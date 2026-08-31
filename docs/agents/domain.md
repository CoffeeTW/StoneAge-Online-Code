# Domain docs

How engineering skills should consume this repository's domain documentation when exploring the codebase.

## Before exploring, read these

- `CONTEXT.md` at the repository root.
- `CONTEXT-MAP.md` at the repository root if it exists; read each referenced context relevant to the task.
- ADRs under `docs/adr/` that affect the area being changed.

If any of these files do not exist, proceed silently. Do not flag their absence or suggest creating them before they are needed. Domain-modeling skills create them lazily when terminology or architectural decisions are actually resolved.

## Layout

This is a **single-context** repository:

```text
/
|-- CONTEXT.md
|-- docs/
|   |-- agents/
|   |   |-- domain.md
|   |   `-- issue-tracker.md
|   `-- adr/
`-- game server source files and domain directories
```

If the repository later becomes a genuine multi-context monorepo, add a root `CONTEXT-MAP.md` and update this file before assuming per-context documentation.

## Use the glossary's vocabulary

When output names a domain concept in an issue title, refactor proposal, hypothesis, or test name, use the terminology defined in `CONTEXT.md`. Do not drift to synonyms the glossary explicitly avoids.

If a needed concept is absent, reconsider whether the term belongs to the project. If it represents a real gap, record it for later domain modeling.

## Flag ADR conflicts

If proposed work contradicts an existing ADR, surface the conflict explicitly instead of silently overriding the decision.
