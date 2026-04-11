# Linux Command Progressions

## Ch. 3 — Manage Local Users and Groups
*New this session:*

| Command/Concept | What it does |
|----------------|-------------|
| `id [user]` | Show UID, GID, and group memberships |
| `su username` | Switch user (non-login shell, keeps env) |
| `su - username` | Switch user (login shell, full env reset) |
| `sudo command` | Run command as root (uses your password) |
| `sudo -i` | Interactive root login shell |
| `sudo -s` | Interactive root shell (no login scripts) |
| `visudo` | Safely edit `/etc/sudoers` |
| `/etc/sudoers.d/` | Drop-in directory for sudo rules |
| `useradd username` | Create new user account |
| `usermod [opts] user` | Modify existing user account |
| `usermod -aG group user` | Append user to supplementary group |
| `usermod -L / -U user` | Lock / unlock user account |
| `userdel [-r] user` | Delete user (optionally remove home dir) |
| `passwd [user]` | Set or change password |
| `groupadd [-g GID] name` | Create new group |
| `groupmod -n new old` | Rename group |
| `groupmod -g GID name` | Change group GID |
| `groupdel name` | Delete group |
| `newgrp groupname` | Temporarily switch primary group |
| `chage -l user` | List password aging info |
| `chage [opts] user` | Set password aging policy |
| `/etc/passwd` | User account database (7 colon fields) |
| `/etc/shadow` | Password hashes and aging info |
| `/etc/group` | Group database (4 colon fields) |
| `/etc/login.defs` | Default UID/GID ranges and password policy |
| `wheel` group | Members get sudo access by default (RHEL 7+) |
| `NOPASSWD:` | Sudoers keyword to skip password prompt |
