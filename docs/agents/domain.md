# Domain 文件

本文件說明工程 skills 在探索 codebase 時，應如何使用本專案的 domain 文件。

## 開始探索前

依序閱讀：

- Repository 根目錄的 `CONTEXT.md`。
- 如果根目錄存在 `CONTEXT-MAP.md`，閱讀其中與目前工作相關的 context。
- `docs/adr/` 中影響目前工作範圍的 ADR。

如果上述檔案不存在，應直接繼續，不需將缺少檔案視為錯誤，也不應在實際需要前建議預先建立。Domain modeling skills 會在術語或架構決策確定後，按需建立文件。

## 文件布局

本專案採用 single-context 布局：

```text
/
|-- CONTEXT.md
|-- docs/
|   |-- agents/
|   |   |-- domain.md
|   |   |-- issue-tracker.md
|   |   `-- triage-labels.md
|   `-- adr/
`-- 遊戲伺服器原始碼與 domain 目錄
```

如果未來 repository 成為真正的 multi-context monorepo，應先新增根目錄 `CONTEXT-MAP.md` 並更新本文件，再採用各 context 獨立文件的假設。

## 使用 glossary 定義的詞彙

當 Issue 標題、重構提案、假設或測試名稱提及 domain concept 時，應使用 `CONTEXT.md` 定義的術語，不應改用 glossary 明確避免的同義詞。

如果需要的 concept 尚未出現在 glossary，應先確認它是否真的是本專案使用的概念。若確實代表 domain 缺口，則記錄並留待後續 domain modeling 處理。

## 標示 ADR 衝突

如果提議的工作與既有 ADR 衝突，必須明確指出衝突，不得默默覆蓋既有決策。
