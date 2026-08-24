# `.ai/` — Project AI Governance

Curated, project-specific AI governance for **z88dk-bench**. Authored manually by the maintainer. Do **not** auto-generate.

## Layout

```text
.ai/
├── README.md       This file (index)
├── skills/         Project-specific skills (Z88DK toolchain, Z80 asm, Makefile rules)
├── instructions/   Domain guides and how-tos (compilation, debugging, testing)
└── templates/      Reusable templates (commit bodies, PR descriptions, issue forms)
```

## How to use

1. Read `agents.md` at the repo root first — it is the entry point.
2. For project-specific tasks, check `.ai/skills/` for matching skills.
3. For domain conventions not covered by a skill, check `.ai/instructions/`.
4. For reusable structures (PR, commit, issue), check `.ai/templates/`.

## Skills index

| Skill | Purpose | Trigger |
| --- | --- | --- |
| `z88dk-toolchain` | How to use `zcc`, `+zx`, clibs, CRTs and pragmas in this project | `z88dk`, `zcc`, `+zx`, `clib`, `CRT`, `pragma` |

When you add a new skill under `skills/<name>/SKILL.md`, add a row here.