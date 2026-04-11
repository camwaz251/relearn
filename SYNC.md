# Cross-Machine Sync (AWS WorkSpaces only)

This file only applies on the AWS WorkSpaces machine, where the repo lives at
`~/Learning/refresh/` and the sync scripts exist at `~/Learning/`.

On any other machine (local workstation, etc.) this file is inert — ignore it.

## Scripts

- `bash ~/Learning/push.sh` — zips `refresh/` and copies to `S3Share/CamsStuff/refresh.zip`
- `bash ~/Learning/pull.sh` — fetches that zip and rsyncs into `refresh/`

## Flow

1. Work on a track on either machine.
2. Commit + push to GitHub as normal (primary sync path).
3. Use `push.sh`/`pull.sh` only when transferring content that is **not** in git
   (e.g. large files under `knowledge/` that are gitignored).
