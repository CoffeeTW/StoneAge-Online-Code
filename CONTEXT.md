# StoneAge Online 領域語言

本文件定義 StoneAge Online Game Server 使用的核心領域語言，讓文件、Issue 與後續設計討論使用一致名稱。它只描述概念與關係；程式結構、啟動程序、協定細節與風險請參閱 docs/architecture.md。

## Language

### Game Server（GMSV）

承載單一遊戲世界執行個體的權威服務，負責連線中的角色、地圖互動、戰鬥、NPC、道具與即時遊戲規則。

_避免：_ 將 GMSV 稱為 Account Server，或假設它獨立保存所有帳號與角色資料。

### Account Server（AC／ACSV）

GMSV 依賴的外部服務，負責帳號驗證、角色資料的載入與保存，以及跨 Game Server 共用的部分資料。

_避免：_ 將 AC 簡化成資料庫；它對 GMSV 提供的是服務與訊息介面。

### Client

玩家操作的遊戲客戶端。Client 向 GMSV 提交登入、移動、互動與戰鬥命令，並接收世界狀態和畫面事件。

### Server Instance（伺服器實例）

一個正在執行的 GMSV 世界節點，具有自己的名稱、識別碼、監聽埠、容量與載入資料集。

_避免：_ 在未指明是程式、程序或世界節點時，籠統使用「Server」。

### Account（帳號）

玩家的驗證身分，可擁有或存取一至多個 Player Character。帳號身分和密碼由 AC 驗證。

### CDKEY

此系統中用來識別帳號的既有名稱。它是帳號識別資訊，不等同 Player Character 名稱。

_避免：_ 在文件中同時用「帳號」、「角色名稱」與「CDKEY」指稱同一件事。

### Character（角色／Chara）

可存在於世界或戰鬥中的通用行動者。Player Character、Pet、Enemy 與 NPC 都是 Character 的不同種類。

_避免：_ 將 Character 自動解讀成玩家；談到玩家控制的角色時使用 Player Character。

### Player Character（玩家角色）

由已連線 Client 控制並隸屬於 Account 的 Character。它持有角色屬性、背包、裝備、寵物、技能與社交狀態。

_避免：_ 單用 Player 指稱 Client、Account 與 Player Character 三者。

### NPC

由伺服器控制、依模板與事件行為提供對話、商店、傳送、任務或其他世界服務的 Character。

### Pet（寵物）

由 Player Character 持有、編隊或出戰的 Character。Pet 可具有自己的屬性與 Pet Skill。

### Enemy（敵人）

由遭遇、NPC 或其他遊戲規則產生，作為戰鬥對手的 Character。Enemy 通常由敵人模板、敵人資料與群組組合而成。

### World Object（世界物件）

放置於 Floor 座標上的可定位事物，可代表 Character、掉落 Item、金錢或 Warp Point。

_避免：_ 將 World Object 和 Character 視為同義詞；Character 只是世界物件可引用的一種類型。

### Map（地圖）

描述一個或多個 Floor 的地形、物件層、可行走性與區域規則的世界資料。

### Floor

具有唯一識別碼、尺寸與名稱的可定位遊戲區域。Character 與 World Object 的位置由 Floor、X、Y 共同表示。

_避免：_ 將 Floor 僅理解為建築樓層；它是本專案對地圖區域的正式稱呼。

### Warp Point（傳送點）

將 Character 從一組 Floor 座標移動到另一組 Floor 座標的世界連接點。

### Encounter（遭遇）

依地圖、位置、機率與敵人群組產生 Battle 的規則或事件。

### Party（隊伍）

由多個 Player Character 組成的臨時協作群組，可共同移動、進入遭遇與參與 Battle。

### Battle（戰鬥）

由兩個 Battle Side 組成、依回合收集命令並結算結果的對戰實例。參與者是 Character，而不是另一套獨立角色資料。

### Battle Side（戰鬥側）

Battle 的其中一方，包含多個 Battle Entry。典型情況是玩家側與敵人側，也可能是玩家對玩家或觀戰情境。

### Battle Entry（戰鬥席位）

Character 在特定 Battle Side 中的參戰位置，保存該次 Battle 所需的加入、逃跑、守護者與獎勵資訊。

### Battle Command（戰鬥命令）

Character 在一個回合選擇的行動，例如攻擊、防禦、捕獲、逃跑、使用 Item、施放 Magic 或使用技能。

### Turn（回合）

Battle 收集參與者命令、決定順序、執行效果並檢查勝負的一次完整循環。

### Item Definition（道具定義）

資料檔定義的 Item 原型，描述識別碼、名稱、類型、可用場景、目標、數值、Magic 與行為。

### Item Instance（道具實例）

由 Item Definition 建立、實際存在於背包、裝備欄、倉庫或世界中的一份 Item。

_避免：_ 在討論數量、所有權或生命週期時，只說 Item 而不區分定義與實例。

### Equipment（裝備）

配置於 Player Character 或 Pet 裝備位置的 Item Instance，會影響屬性或提供附加效果。

### Magic（魔法）

由識別碼、可用場景、目標規則與效果行為構成的能力。Magic 可由 Item、Battle Command 或其他技能流程觸發。

_避免：_ 將所有技能都稱為 Magic；Pet Skill 與 Profession Skill 是不同概念。

### Pet Skill（寵物技能）

Pet 可使用的能力，通常在 Battle 中轉換成特定 Battle Command 或效果。

### Profession Skill（職業技能）

Player Character 依職業取得的能力，具有獨立的技能資料與 Battle 行為。

### Status Effect（狀態效果）

作用於 Character 或 Battle 的持續性狀態，例如中毒、麻痺、睡眠、石化或其他增益與減益。

### Family（家族）

玩家組成的長期社交組織，具有成員、領導、聲望、據點與跨伺服器保存需求。

_避免：_ 使用 Guild 取代既有正式名稱 Family，除非同時說明兩者在語境中等價。

### Manor（莊園）

與 Family 競爭、據點或排名相關的世界領域概念。

### Character Save（角色存檔）

Player Character 可跨連線保存與還原的持久化狀態。GMSV 產生或消費角色資料，AC 負責其服務端保存流程。

### Game Data（遊戲資料）

啟動時載入、共同決定世界與規則的資料集合，包括地圖、NPC、Item、Magic、Enemy、Encounter、Pet Skill 與其他設定。

_避免：_ 將 Game Data 和 setup.cf 混為一談；前者描述遊戲內容，後者描述伺服器執行設定與資料路徑。

## 核心概念關係

    Account ──擁有／存取──> Player Character ──由──> Client 控制
       │                         │
       │                         ├──持有──> Item Instance ──源自──> Item Definition
       │                         ├──持有──> Pet ──使用──> Pet Skill
       │                         ├──加入──> Party
       │                         └──加入──> Family
       │
       └──由 Account Server 驗證與保存

    Floor ──包含──> World Object ──可引用──> Character／Item／金錢／Warp Point

    Encounter ──產生──> Battle ──包含兩個──> Battle Side
                                      └──包含──> Battle Entry ──引用──> Character

    Battle Command ──可使用──> Item／Magic／Pet Skill／Profession Skill

    GMSV ──執行世界與 Battle──> Character／Map／NPC／Game Data
    GMSV ──委託驗證與持久化──> Account Server
