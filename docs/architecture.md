# StoneAge-Online-Code 專案架構

本文件記錄目前原始碼可證明的 GMSV 架構、啟動與資料流程。它描述的是現況，不代表推薦設計，也不推測未留下證據的歷史決策。

## 文件基準與可信度

- 分析路徑：D:\新增資料夾\gmsv-code2026
- Git 分支：original-baseline
- Git commit：69267e5f8ccd10acb406a355649f0ccd7034cefe
- 分析日期：2026-08-31
- 原始碼規模：304 個 .c／.h 檔，約 152,809 行。
- 本次只建立文件，沒有修改 .c、.h、Makefile 或遊戲資料。

本文使用以下標示：

- **已確認**：可由目前 repository 的程式、Makefile 或檔案樹直接證明。
- **推論**：由多個已確認事實推導出的架構判讀，仍需執行環境或系統擁有者驗證。
- **未知**：目前 repository 不包含足夠證據。

程式參照使用「檔案:起始行-結束行」。行號以本文件基準 commit 為準，未來修改可能使行號漂移。

## 1. 系統邊界

**已確認**

    Game Client
        │
        │ LSSPROTO：登入、移動、互動、戰鬥與畫面事件
        ▼
    GMSV（本 repository）
        │
        │ SAACPROTO：驗證、角色載入／保存、Family 與共享資料
        ▼
    Account Server（外部，原始碼不在本 repository）

    setup.cf + Game Data
        └───────────────> GMSV 啟動時載入

本 repository 的主要產物是 gmsv。GMSV 對 Client 開放監聽埠，同時主動連線到 Account Server。初始化流程在連上 AC 後送出 ACServerLogin；登入失敗會終止程序（init.c:643-683、callfromac.c:55-64）。

**推論**

GMSV 是即時遊戲世界的權威程序；AC 是身分、角色持久化與部分跨 GMSV 狀態的權威服務。這個邊界由 CHAR 登入／保存與 Family 訊息方向支持，但完整 AC 實作不在本 repository。

**未知**

- Account Server 的實作、版本、資料庫 schema、備援與一致性模型。
- Client 原始碼及其封包重送、加密、版本協商和錯誤處理。
- 實際部署是否由多個 GMSV 共用一個 AC，以及跨 GMSV 的拓撲。

## 2. Server 啟動流程

### 2.1 程序入口

**已確認**

main 的高階順序如下（main.c:52-95）：

1. setNewTime 更新全域 NowTime。
2. util_Init 初始化共用工具／記憶體支援。
3. LoadAnnounce 從目前工作目錄的 ./announce.txt 載入登入公告；此時 setup.cf 尚未讀取（main.c:64-71、configfile.c:672-681）。
4. init 解析參數、讀取設定、建立核心陣列、載入 Game Data、啟動協定並連線 AC。
5. LoadPetTalk 及啟用功能對應的額外資料。
6. mainloop 進入不返回的主迴圈。

命令列選項由 init.c:45-100 定義：

- -d debuglevel：除錯層級。
- -f configfilename：設定檔；預設 setup.cf。
- -h：顯示使用方法，但目前流程將其視為 init 失敗並以錯誤碼結束。

### 2.2 init 初始化順序

**已確認**

| 階段 | 主要動作 | 證據 |
|---|---|---|
| 基本設定 | defaultConfig、signalset、命令列與環境解析 | init.c:140-166 |
| 設定生效 | 讀取 setup.cf、設定 nice、編碼 key 與 AC write buffer | init.c:166-192 |
| 記憶體 | configmem、memInit | init.c:439-443 |
| Socket | initConnect；持續重試 bindlocalhost 直到監聽埠成功 | init.c:445-456 |
| 世界索引池 | Object、Char、Item instance、Battle 陣列 | init.c:459-477 |
| 動態行為 | 建立共用函式名稱對照表 | init.c:480-482 |
| 世界規則資料 | 無敵區、出生點、稱號、Encounter、Enemy、Magic、Pet Skill、Profession Skill、Item 合成與效果 | init.c:485-583 |
| Map | 載入圖像／地圖資料 | init.c:634-636 |
| NPC | 載入 NPC template 與 create 設定 | init.c:638-641 |
| Client protocol | 初始化 LSSPROTO server 工作區 | init.c:643-645 |
| Account Server | connectHost、初始化 AC connection buffer、初始化 SAACPROTO client | init.c:647-674 |
| GMSV 註冊 | 組合登入字串並送出 ACServerLogin | init.c:677-685 |
| Log | 設定 protocol log 並初始化一般 log | init.c:688-704 |

任一關鍵資料載入失敗通常經 goto 清理路徑使 init 回傳 FALSE，因此地圖、NPC、核心資料與 AC 都是啟動必要條件。

### 2.3 mainloop

**已確認**

mainloop 先生成 NPC、註冊 SIGUSR1／SIGUSR2，再初始化 Warp Point、效能監測、Chat Room 等啟用功能（main.c:98-145）。

每輪主要順序如下（main.c:147-239）：

1. 依 CPUUSE 設定選擇性 usleep。
2. 更新 NowTime，處理每日 log 備份判定。
3. netloop_faster：接受連線、讀取／派送封包、輸出 write buffer。
4. NPC_generateLoop(0)：生成或更新 NPC。
5. BATTLE_Loop：推進所有使用中的 Battle 狀態機。
6. CHAR_Loop：處理玩家與其他 Character 的走動及 loop callback。
7. PETMAIL_proc、family_proc、chardatasavecheck。
8. 啟用功能的 Angel 與效果檢查。
9. ShutdownProc。

**推論**

程式雖連結 pthread 且 Connection 內有 mutex，但目前原始碼沒有 pthread_create；核心遊戲邏輯看起來由單一 mainloop 依序驅動。這降低一般資料競爭，但使某個模組的長時間操作可阻塞整個世界迴圈。

## 3. 核心模組與目錄責任

**已確認**

| 位置 | 主要責任 | 代表檔案 |
|---|---|---|
| 根目錄 | 程序入口、初始化、設定、網路、協定接線、時間、Object、log 與共用工具 | main.c、init.c、configfile.c、net.c、callfromcli.c、callfromac.c、object.c、function.c |
| char/ | 通用 Character 模型，以及玩家、Pet、Enemy、Party、Encounter、Family、Trade、Chat、移動、道具欄與存檔 | char_base.c、char.c、char_item.c、char_walk.c、pet.c、enemy.c、encount.c、family.c |
| npc/ | NPC template／create／generate 基礎設施，以及商店、傳送、銀行、任務、Family、競賽等具體 NPC 行為 | npctemplate.c、npccreate.c、npcgen.c、readnpc.c、npc_*.c |
| map/ | Floor 與 map image data 載入、座標檢查、tile／object layer、座標物件鏈結、Warp Point | readmap.c、map_deal.c、map_util.c、map_warppoint.c |
| item/ | Item Definition、Item Instance 池、資料解析、使用／裝卸／掉落事件、合成與交易 | item.c、item_event.c、item_gen.c、item_trade.c |
| battle/ | Battle 陣列與狀態機、命令解析、行動結算、AI、Battle Item／Magic、Pet Skill、Profession Skill | battle.c、battle_command.c、battle_event.c、battle_magic.c、battle_item.c |
| magic/ | Magic Definition 載入、ID 查找、函式派送，以及場上／場外魔法效果 | magic_base.c、magic.c、magic_field.c |
| include/ | 上述模組的公開型別、enum、巨集、全域變數宣告與函式介面 | char_base.h、battle.h、item.h、magic_base.h、net.h、readmap.h |

Makefile 將 char、npc、map、item、magic、battle 各自編成靜態庫，再與根目錄物件檔連結成 gmsv（makefile:12-31）。

**推論**

目錄是建置邊界，不是嚴格的架構邊界。include graph 顯示 char、battle、item、magic、npc 間存在雙向依賴；例如 magic 直接讀 Character、Item 與 Battle，而 battle 也直接使用 Magic、Item、NPC 與 Map。

## 4. char／battle／item／magic 關係

### 4.1 Character 是共同實體

**已確認**

Char 結構把持久資料、字串、flags、Item 索引、Pet／Skill、Title、Address Book、work data 與 callback 指標集中在同一結構（include/char_base.h:1385-1422）。全域 CHAR_chara 指向配置後的 Character pool（char/char_base.c:26-31、include/char_base.h:1497）。

Character 的 battle work slots 包含 CHAR_WORKBATTLEMODE、CHAR_WORKBATTLEINDEX、CHAR_WORKBATTLESIDE 與多個 CHAR_WORKBATTLECOM 欄位（include/char_base.h:750-759）。

### 4.2 Battle 引用 Character

**已確認**

BATTLE_ENTRY 以 charaindex 引用 Character；BATTLE_SIDE 持有最多十個 entry；BATTLE 包含兩側、mode、type、turn、場地屬性及 callback（include/battle.h:415-497）。所有 Battle 位於全域 BattleArray（battle/battle.c:43-45）。

BATTLE_Loop 掃描 BattleArray，依 mode 呼叫 Init、Command、Finish、Stop 或觀戰狀態處理（battle/battle.c:3980-4028）。命令收齊後，Battle 先執行兩側 AI，再進入 BATTLE_Battling 結算（battle/battle.c:3901-3950）。

### 4.3 Character 持有 Item Instance 索引

**已確認**

Char 的 indexOfExistItems 與倉庫欄位保存 Item Instance pool 的索引，而不是把完整 Item 複製進 Character（include/char_base.h:1399-1407）。

ITEM_table 表示讀入的定義資料，ITEM_exists 表示是否使用中的實例槽；兩者都包住 ITEM_Item（include/item.h:292-313）。Item Instance pool 是 item/item.c 內的 ITEM_item，Character 與 Item 透過整數索引互相定位（item/item.c:20-23、char/char_item.c:734-754）。

### 4.4 Item 可驅動 Magic 與其他函式

**已確認**

ITEM_Item 同時保存整數資料、字串資料、work data 和 void* callback table（include/item.h:292-299）。Item 的字串欄位可指定 INIT、USE、ATTACH、DETACH、DROP、PICKUP 等函式名稱（include/item.h:220-267）。

function.c 將函式名稱映射到函式指標，啟動時檢查名稱唯一性並計算 hash；Item instance 建立時再把資料中的名稱解析到 callback table（function.c:700-742、item/item.c:513-527、item/item.c:664-683）。

一般使用 Item 時，CHAR_ItemUse 取得 ITEM_USEFUNC 並呼叫它（char/char_item.c:734-754）。Battle 中的 Item 命令先存入 Character 的 CHAR_WORKBATTLECOM 欄位，結算時再呼叫 CHAR_ItemUse（battle/battle_command.c:393-419、battle/battle.c:7953-8018）。

### 4.5 Magic 由 ID 與函式名稱派送

**已確認**

Magic 定義包含 ID、使用場景、目標，以及 NAME、FUNCNAME、OPTION 等字串欄位（include/magic_base.h:8-61）。MAGIC_initMagic 載入 Magic table；MAGIC_getMagicArray 將 magic ID 解析成陣列位置（magic/magic_base.c:137-180、magic/magic_base.c:400-413）。

MAGIC_Use 的典型路徑是：

    Character 的背包位置
        → Item Instance
        → ITEM_MAGICID
        → Magic Definition
        → MAGIC_FUNCNAME
        → MAGIC_CALLFUNC
        → 實際效果函式

此流程可見於 magic/magic.c:26-65。Battle 中的魔法命令使用 CHAR_WORKBATTLECOM2／3 保存目標、Magic ID 與 Item 位置，結算時呼叫 MAGIC_DirectUse（battle/battle.c:7915-7951）。

### 4.6 關係總結

**推論**

    Char 是狀態中心
      ├──用索引持有 Item Instance
      ├──用 work slots 連到 Battle 與待執行命令
      └──同時代表 Player／Pet／Enemy／NPC

    Battle 是協調器
      ├──以 charaindex 組成兩側
      ├──讀寫 Char 的 battle work slots
      └──委派給 attack／item／magic／skill 效果

    Item 與 Magic 是資料驅動的能力入口
      └──資料中的名稱必須與編譯進 binary 的函式表完全一致

因此 char、battle、item、magic 不是可獨立替換的四層，而是共享索引、enum、work slots 與函式表的緊密協作核心。

## 5. Client ↔ GMSV：LSSPROTO

### 5.1 Connection 與 I/O

**已確認**

每個 fd 對應一個 CONNECT，保存 read／write buffer、來源類型、登入狀態、CDKEY、密碼、角色名稱、charaindex、節流計數與視窗互動狀態（net.c:76-245）。LoginType 與 ConnectType 定義於 include/net.h:30-53。

netloop_faster 使用零 timeout select：

1. 檢查 listening socket 並 accept 新連線（net.c:2089-2110）。
2. 輪流選擇一個有效 fd，讀入 connection read buffer（net.c:2480-2543）。
3. 每個 fd 每輪最多取三個 newline-delimited message（net.c:2553-2572）。
4. acfd 交給 SAACPROTO dispatcher，其他 fd 交給 LSSPROTO dispatcher（net.c:2559-2569）。
5. 定時送出 CA／CD 合併 buffer，再將 write buffer 寫回 socket（net.c:2578-2620）。

LSSPROTO write function 最終只把編碼後訊息放入 Connection write buffer；buffer overflow 會要求關閉該 connection（net.c:474-495）。

### 5.2 LSSPROTO 派送

**已確認**

lssproto_InitServer 建立 protocol 共用工作區（lssproto_serv.c:17-45）。lssproto_ServerDispatchMessage 進行 decode、依 SEPARATOR 分割、讀取功能 ID、解碼參數、比對加總 checksum，再呼叫 lssproto_*_recv application handler（lssproto_serv.c:63-100；後續 case 採相同模式）。

application handler 集中在 callfromcli.c，涵蓋登入、建立角色、移動、Map、Item、Pet、Talk、Event、Battle command、商店、Family、Trade 與其他 Client 操作。

    socket bytes
        → Connection read buffer
        → newline frame
        → util_DecodeMessage
        → function ID + decoded arguments + checksum
        → lssproto_*_recv
        → Char／Map／Battle／Item 等領域函式
        → lssproto_*_send
        → Connection write buffer

### 5.3 登入與角色載入範例

**已確認**

    Client
      │ ClientLogin(CDKEY, password)
      ▼
    lssproto_ClientLogin_recv
      │ 保存 connection 身分，送 ACCharLogin
      ▼
    Account Server
      │ ACCharLogin result
      ▼
    saacproto_ACCharLogin_recv
      │ 回應 Client 可用角色流程
      ▼
    Client
      │ CharLogin(character name)
      ▼
    lssproto_CharLogin_recv
      │ 送 ACCharLoad，state = WHILELOGIN
      ▼
    Account Server
      │ ACCharLoad result + serialized character
      ▼
    saacproto_ACCharLoad_recv
      │ 成功時
      ▼
    CHAR_login

入口與送出位置是 callfromcli.c:67-95、callfromcli.c:186-205；AC 載入回覆與 CHAR_login 位於 callfromac.c:104-119。

**未知**

- Client 使用的完整 LSSPROTO 版本與產生器。
- util_DecodeMessage 的設計目標是否包含保密性；目前只能確認有編碼與加總 checksum，不能宣稱具有密碼學安全性。
- Client 與 GMSV 對丟包、重連、封包重播及版本不一致的完整策略。

## 6. GMSV ↔ Account Server：SAACPROTO

### 6.1 連線與訊息格式

**已確認**

GMSV 啟動時 connectHost 到設定的 AC host／port，將該 connection 標成 AC，初始化 SAACPROTO client 後送出 ACServerLogin（init.c:647-683）。

SAACPROTO send functions 以 saacproto_CreateHeader 建立文字函式名稱，例如 ACServerLogin、ACCharLoad、ACCharSave、DBUpdateEntryString、Broadcast 與 Family 相關操作（saacproto_cli.c:34-264、saacproto_cli.c:335-661）。

saacproto_ClientDispatchMessage 分割訊息、取得 funcname，再以 strcmp 鏈派送到 callfromac.c 的 callback（saacproto_cli.c:668-754）。其責任包括：

- GMSV 註冊與關閉。
- 帳號登入、角色列表、載入、保存與刪除。
- Lock／Kick 與上線狀態。
- 泛用 DB key／value 與排名操作。
- Broadcast／Message。
- Family／Manor／Auction。
- Item／Pet pool 與 mission 等啟用功能。

### 6.2 失效行為

**已確認**

- ACServerLogin 回覆不是 successful 時，GMSV 呼叫 shutdownProgram 並 exit（callfromac.c:55-64）。
- mainloop 中讀取 acfd 得到 EOF 或不可恢復錯誤時，程序也進入 shutdown 並 exit（net.c:2517-2523）。

**推論**

目前 GMSV 將 AC 視為必要依賴，而非可暫時降級的附屬服務。AC 中斷會使整個遊戲世界停止，以避免繼續運作但無法驗證或保存角色。

**未知**

- AC 是否具備交易式保存、冪等 request ID、重試或重複訊息去除。
- Character Save 的序列化格式版本與升級策略。
- Family／Manor 等跨 GMSV 資料的衝突解決方式。

## 7. 重要資料結構與全域狀態

**已確認**

| 狀態 | 位置 | 關係與生命週期 |
|---|---|---|
| CHAR_chara | char/char_base.c:26-31 | 所有 Character 的全域 pool；容量在 init 時由玩家、Pet 與 other character 上限決定 |
| BattleArray／BATTLE_battlenum | battle/battle.c:43-45 | 所有 Battle 的全域 pool；BATTLE_ENTRY 以 charaindex 回指 CHAR_chara |
| ITEM_item | item/item.c:20-23 | 所有使用中 Item Instance 的私有全域 pool；Character 保存其索引 |
| ITEM_tbl | item/item.c:416-418 | Item Definition table；依 feature flag 可為固定陣列或動態配置 |
| MAGIC_magic | magic/magic_base.c:11-19 | Magic Definition table；另有 Attack Magic table |
| obj／objnum | object.c:20-38 | World Object pool，記錄 type、引用 index 與 Floor／X／Y |
| MAP_Map | include/readmap.h:15-27 | 每個 Floor 的尺寸、tile、object layer 與座標 object linked list |
| Connect | net.c:90-245 | fd-indexed connection pool，保存 I/O、登入與節流狀態 |
| servstate | net.c:76-89、net.c:253-261 | 是否接受新連線、shutdown 狀態與 server fd generation |
| config | configfile.c:28-292 | 單一全域 Config，透過大量 getter 被所有模組讀取 |
| NowTime | include/handletime.h:8-18 | mainloop 更新、全系統共用的時間快照 |
| NPC_template／NPC_create | include/npctemplate.h:99、include/npccreate.h:75 | NPC 模板與生成設定的全域陣列 |

World Object 的 type 可為 Character、Item、Gold 或 Warp Point；其 index 欄位依 type 指向不同 pool（include/object.h:6-35）。Map 的每個座標維護 object index linked list（include/readmap.h:6-27、include/readmap.h:108-114）。

**推論**

此架構的實體 identity 主要是「全域 pool 中的整數索引」。跨模組交換成本低，但索引有效性、槽位重用與生命週期順序是系統正確性的核心不變條件。

## 8. 設定檔與資料載入流程

### 8.1 setup.cf

**已確認**

defaultConfig 只先設定程式名稱與預設 setup.cf（configfile.c:1834-1851）。readconfigfile 先嘗試 setup.cf.<短 hostname>，不存在才退回原檔名（configfile.c:1960-1990）。

每行採 key=value；空白、註解與空行會被處理，再依 readconf table 把值寫入全域 Config。載入完成後 lastConfig 將多個相對資料路徑加上 topdir，包括 mapdir、maptilefile、battlemapfile、itemfile、invfile、appearfile、effectfile、quizfile、title、protocol log 與 npcdir（configfile.c:1861-1921、configfile.c:1992-2063）。

核心設定類別：

- AC：acserv、acservport、acpasswd、gameservname／ID。
- Client listener：port、reuseaddr、socket buffer。
- 容量：fdnum、petcharnum、otherscharnum、objnum、itemnum、battlenum。
- 路徑：topdir、mapdir、maptilefile、itemset、npcdir、各種規則資料檔與 log。
- loop／network：one loop time、CA／CD send interval、AC write size、允許錯誤數。
- 大量 feature-specific 參數，其存在與 version.h 的編譯旗標一致。

### 8.2 Game Data 載入依賴

**已確認**

    setup.cf
      ├──容量──> Object／Character／Item Instance／Battle／Connection pools
      ├──路徑──> Map／NPC／Item／Magic／Enemy／Encounter／Skill 等資料
      ├──網路──> Client listener 與 Account Server
      └──節奏──> mainloop、buffer 與 autosave 相關參數

主要載入順序是：

1. Item Definition，接著 Item Instance pool。
2. Battle pool 與動態函式表。
3. Character 世界規則：出生、稱號、Encounter、Enemy。
4. Magic、Attack Magic、Pet Skill、Profession Skill。
5. Item atom／合成 cache／random table。
6. Map。
7. NPC template 與 create files。
8. Protocol、AC 與 Log。

順序證據位於 init.c:459-704。這表示後載入模組可依賴先前已建立的 pool 與函式表；調換順序不是純粹的整理工作。

**未知**

- 正式環境 setup.cf 的鍵和值。
- 所有資料檔的實際 encoding、版本與生成來源。
- 哪些資料檔可在執行中 reload，以及 reload 是否為原子操作。

## 9. 編譯與執行條件

### 9.1 編譯

**已確認**

根 Makefile 使用 GCC／GNU99，並要求 POSIX shell 與一般 Unix 工具。主要旗標包含：

- -fcommon
- -march=x86-64
- -std=gnu99
- -fgnu89-inline
- -O1
- -ggdb3
- -fPIC
- -D_NEW_DECODE
- -w 以及數個允許舊式 implicit declaration／implicit int 的選項

連結依賴為 mysqlclient、zlib、libm、pthread 與 dl（makefile:1-29）。子目錄分別建立 libchar.a、libnpc.a、libmap.a、libitem.a、libmagic.a、libbattle.a，最後連成 ./gmsv（makefile:12-41）。

預期命令：

    make

### 9.2 執行

**已確認**

預期命令：

    ./gmsv
    ./gmsv -d <debuglevel>
    ./gmsv -f <config-file>

最低執行前置條件：

- 可用的 setup.cf 或 setup.cf.<hostname>。
- 設定指向的全部 Game Data。
- 可 bind 的 Client listener port。
- 可連線且協定相容的 Account Server。
- 可寫入的 log／store 位置。

目前 repository 不包含 setup.cf、完整 data directory、gmsv binary、Client 或 Account Server，因此本次未宣稱可從乾淨 checkout 直接啟動。

Makefile 沒有 test target；repository 也沒有可辨識的自動測試或 CI 設定。README.md 只有專案標題，未提供環境建置或資料版本說明。

**推論**

- 目標環境是 Linux／類 Unix；程式使用 getopt、nice、usleep、POSIX socket 與 /bin/sh。
- mysqlclient 雖被連結，但本 repository 的 .c／.h 沒有 MySQL API 參照；它可能是歷史依賴或外部建置慣例，仍需實際 link 環境驗證。

## 10. 高耦合區域

### 10.1 全域 pool 與裸索引

**已確認**

Character、Battle、Item、Object、Map 與 Connection 都是容量固定或啟動時配置的全域 pool，模組間多以 int index 連結。Battle、背包、Map object list 與 connection 都直接持有其他 pool 的索引（include/char_base.h:1390-1422、include/battle.h:421-497、include/object.h:18-35、net.c:90-245）。

**推論**

任何 index 生命周期錯誤都可能跨越多個模組；新增欄位或調整分配策略前，必須同時檢查 create、attach、detach、save、logout、battle finish 與 pool slot reuse。

### 10.2 data enum 與 work slot

**已確認**

Char 與 Item 以大型 enum 作為 data[]、string[]、workint[] 的位置契約。Battle 命令、暫態效果、NPC 工作資料與 feature-specific 欄位共用這些陣列（include/char_base.h:371-1269、include/item.h:92-299）。

**推論**

enum 排序、條件編譯與存檔格式很可能互相依賴。即使只是插入 enum 成員，也可能改變序列化資料或不同 binary 間的 ABI／資料解讀。

### 10.3 資料名稱到函式指標

**已確認**

NPC、Character、Item 與 Magic 的資料可保存函式名稱，執行時由函式表解析成 void* 或特定 callback（function.c:133-698、function.c:700-742、magic/magic_base.c:25-71、magic/magic_base.c:422-439）。

**推論**

資料檔名稱、編譯進 binary 的 feature flags、函式簽名與 callback slot 必須同步；錯字或錯誤 cast 可能直到特定內容被觸發才出現。

### 10.4 條件編譯

**已確認**

目前 include/version.h 靜態掃描有 386 個啟用中的底線 feature define。這些旗標改變 struct 欄位、enum、資料鍵、函式表與協定 handler；例如 _PROFESSION_SKILL、_CHAR_POOLITEM、_CHAR_POOLPET 與 _ATTACK_MAGIC。

**推論**

version.h 不是單純功能清單，而是此 binary 的資料與協定 schema。不同旗標組合之間未必相容。

## 11. 已確認風險

本章只記錄，不在本階段修改、修復或重構。

### R1. 核心 mainloop 被效能巨集包覆

- **已確認**：netloop_faster、NPC_generateLoop、BATTLE_Loop、CHAR_Loop、保存與 shutdown 等核心呼叫全部位於 #ifdef _ASSESS_SYSEFFICACY_SUB 內（main.c:170-238）。
- **已確認**：目前 version.h 同時啟用 _ASSESS_SYSEFFICACY 與 _ASSESS_SYSEFFICACY_SUB（include/version.h:218-219）。
- **推論**：若未來為了關閉效能量測而移除 _ASSESS_SYSEFFICACY_SUB，binary 仍可編譯，但 mainloop 將不再執行核心工作。

### R2. LSSPROTO return buffer 疑似配置錯誤

- **已確認**：lssproto_InitServer 接收 worksiz，其他 wrapper 依 worksiz 配置，但 ret_work 使用 calloc(1, sizeof(worksiz))（lssproto_serv.c:17-40）。
- **推論**：sizeof(worksiz) 是 int 本身的大小，不是要求的工作區大小；若 ret_work 被當成 worksiz buffer 使用，存在越界寫入風險。
- **未知**：實際觸發路徑、編譯器／平台上的破壞範圍。

### R3. setup.cf 的 OFF 被寫成 1

- **已確認**：readconfigfile 對 ON 寫入 1.0，對 OFF 也寫入 1.0（configfile.c:2040-2051）。
- **推論**：使用 ON／OFF 的數值設定無法藉 OFF 關閉，且可能與維運人員直覺相反。

### R4. 明文認證資訊輸出

- **已確認**：debuglevel 至少為 1 時，init 會輸出 AC password（init.c:195-210）。
- **已確認**：ClientLogin 無條件輸出 CDKEY、password 與來源 IP（callfromcli.c:67-94）。
- **影響**：console、service log 或集中式 log 可能保存可直接使用的認證資訊。

### R5. 固定關機密碼

- **已確認**：Client 可到達的 lssproto_Shutdown_recv 將輸入與固定字串 hogehoge 比較（callfromcli.c:1717-1725）。
- **推論**：若該 handler 可由未受信任 Client 呼叫，固定共享密碼形成遠端可猜測的高影響控制面。
- **未知**：網路邊界是否另有 ACL、防火牆或 protocol-level 限制。

### R6. AC 登入字串含硬編碼常數與固定小 buffer

- **已確認**：GMSV 使用 char buff[50] 和 sprintf 組合 gogo6302-<AC password>-6333（init.c:677-683）。
- **推論**：認證格式與 magic constant 無版本說明；若 password 長度超出預期，固定 buffer 也可能溢位。

### R7. 每秒效果檢查條件疑似永遠為 false

- **已確認**：mainloop 先執行 tmOld = tmNow，下一行才判斷 tmOld.tm_sec != tmNow.tm_sec（main.c:220-225）。
- **推論**：該條件在單執行緒連續敘述中不會成立，因此 CHAR_checkEffectLoop 可能永遠不被這條路徑呼叫。
- **未知**：效果是否另有其他檢查路徑足以補償。

### R8. 大量未受型別系統保護的 callback

- **已確認**：Char 與 Item 儲存 void* callback；呼叫端再 cast 成不同簽名（include/char_base.h:1414-1418、include/item.h:292-299、char/char_item.c:734-754）。
- **推論**：資料名稱映射到錯誤簽名時，C 編譯器無法完整驗證呼叫慣例與參數。

### R9. 固定大小 buffer 與舊式字串 API 廣泛存在

- **已確認**：靜態掃描在目前 .c／.h 中找到大量 sprintf、strcpy、strcat 與 sscanf；代表例包括 callfromcli.c:82-94、saacproto_cli.c:668-675、init.c:677-683。
- **推論**：輸入長度、資料檔格式或協定欄位變化可能導致 buffer overflow、截斷或未終止字串。此掃描只指出攻擊面，不代表每一處都可利用。

### R10. 編譯警告被整體抑制

- **已確認**：根 Makefile 使用 -w，並允許 implicit function declaration、implicit int 與 return mismatch 類型的舊式程式（makefile:8-10）。
- **推論**：64-bit pointer／int、函式簽名與缺少 prototype 問題可能被編譯成功而延後到 runtime。

### R11. AC 是單點必要依賴

- **已確認**：啟動無法連上 AC 會失敗；執行中 acfd 斷線會使 GMSV shutdown／exit（init.c:647-674、net.c:2517-2523）。
- **推論**：AC 故障可同時造成登入、保存與整個世界可用性中斷。

### R12. 輪詢式單主迴圈的延遲傳播

- **已確認**：核心模組依序在 mainloop 執行；netloop_faster 對 listening fd 及被輪到的 connection 使用零 timeout select（main.c:147-239、net.c:2089-2106、net.c:2480-2505）。
- **推論**：昂貴 NPC、Battle、Character loop 或同步檔案／AC 操作會增加所有玩家看到的 tick 延遲；connection 數量上升也會增加輪詢等待時間。

### R13. 註解與資料編碼不明

- **已確認**：目前工具以一般 UTF-8／系統預設解碼時，大量中文／日文註解呈現 mojibake；原始識別字仍可讀。
- **未知**：原始檔預期是 Big5、Shift-JIS、其他 code page 或混合編碼。
- **影響**：未先建立 encoding 規則就重存檔案，可能造成大範圍非功能性 diff 或資料內容損壞。

### R14. 缺少可重現環境與自動驗證

- **已確認**：repository 沒有 setup.cf、完整 Game Data、自動測試、CI 或可執行環境文件；README.md 只有標題。
- **推論**：目前無法由 repository 單獨重現正式 binary、啟動成功或 protocol 相容性。

## 12. 尚未確認的未知事項

以下未知事項應透過實際部署資產、系統擁有者訪談或受控執行環境確認；不應只靠原始碼猜測。

### 執行與部署

- 正式支援的 Linux distribution、GCC、glibc、libmysqlclient 與 zlib 版本。
- 正式啟動命令、工作目錄、service manager、ulimit、port 與檔案權限。
- setup.cf、Game Data、log／store directory 的交付與版本管理方式。
- 多個 GMSV、AC 與資料庫的實際拓撲、容量與 failover。

### 資料與相容性

- Character Save、Item、NPC、Map、Magic 與其他資料檔的 schema 版本。
- version.h 旗標與 Client／AC／Game Data 版本的正式相容矩陣。
- 原始碼和資料檔的正確文字編碼。
- enum／work slot 變動是否會破壞既有角色存檔。

### Protocol 與安全

- LSSPROTO／SAACPROTO 的正式 specification 與 generator 來源。
- 編碼、key、checksum 的威脅模型；是否另有 TLS、VPN 或私有網路保護。
- 管理封包、Shutdown、GM command 的正式授權邊界。
- 密碼在 AC 端的保存方式、傳輸保護與輪替方法。
- 封包 fuzzing、rate limiting 與 replay protection 的實際覆蓋。

### 遊戲規則

- Battle 各 mode／command 的完整狀態轉移與超時規則。
- Item／Magic／Pet Skill／Profession Skill 的資料設計規範與內容製作流程。
- Family、Manor、Auction、Mission 的跨伺服器一致性與營運規則。
- 線上 reload、關機保存和 crash recovery 是否有正式操作手冊。

### 品質與維運

- 是否存在 repository 外部的測試工具、封包模擬器、測試 Client 或 staging data。
- 現行監控指標、log retention、備份與角色資料復原流程。
- 目前 production 使用的 commit、patch set 與 version.h 是否就是本文件基準。

## 13. 後續文件與 ADR 原則

- 領域詞彙與概念關係維護在根目錄 CONTEXT.md。
- 本文件持續記錄可由現況證明的架構、風險與未知事項。
- docs/adr/ 只在團隊實際做出具長期影響、存在取捨且不易逆轉的設計決策時新增。
- 不從現有程式碼反推並虛構歷史 ADR。
- 未來每次更新重要結論時，應更新基準 commit、可信度標示與檔案行號。
