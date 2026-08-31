# Issue tracker：GitHub

本 repository 的 Issue 與規格存放於 `CoffeeTW/StoneAge-Online-Code` 的 GitHub Issues。所有操作使用 `gh` CLI。

## 操作慣例

- 建立 Issue：`gh issue create --title "..." --body "..."`。多行內容應使用 heredoc。
- 讀取 Issue：`gh issue view <number> --comments`，並一併檢查 labels。
- 列出 Issue：使用 `gh issue list --state open --json number,title,body,labels,comments`，依需求加入 label 與 state 篩選條件。
- 留言：`gh issue comment <number> --body "..."`。
- 套用 label：`gh issue edit <number> --add-label "..."`。
- 移除 label：`gh issue edit <number> --remove-label "..."`。
- 關閉 Issue：`gh issue close <number> --comment "..."`。

在本機 checkout 內執行時，由 `git remote -v` 判定 repository；`gh` 通常會自動完成此判定。

## Pull Request 是否納入 triage

**PR 作為需求來源：否。**

只有未來專案明確決定將外部 Pull Request 視為功能需求時，才將此設定改為「是」。

GitHub Issues 與 Pull Requests 共用編號空間。當 `#42` 之類的引用無法判定類型時，先執行 `gh pr view 42`，失敗後再執行 `gh issue view 42`。

## Skill 操作規則

- Skill 要求「publish to the issue tracker」時，建立 GitHub Issue。
- Skill 要求「fetch the relevant ticket」時，執行 `gh issue view <number> --comments`。
- 除非目前的使用者要求已授權寫入，否則不得建立、修改、加上 label、關閉 Issue 或留言。

## Wayfinder 操作

使用 `/wayfinder` 時：

- Map 是一個帶有 `wayfinder:map` label 的 GitHub Issue。
- Child ticket 優先使用 GitHub sub-issue 連結至 map。
- 如果 repository 無法使用 sub-issue，則將 child 加入 map 的 task list，並在 child 內容開頭加入 `Part of #<map>`。
- Child label 使用 `wayfinder:<type>`，其中 type 為 `research`、`prototype`、`grilling` 或 `task`。
- Blocker 優先使用 GitHub 原生 Issue dependencies 表示。
- 如果無法使用 dependencies，則在 child 內容開頭加入 `Blocked by: #<n>`。
- Claim ticket 使用 `gh issue edit <number> --add-assignee @me`；此操作屬於寫入，必須獲得目前要求授權。
- Resolve ticket 包含留下結果留言、關閉 Issue，以及更新 map 的決策紀錄；這些操作同樣必須獲得目前要求授權。
