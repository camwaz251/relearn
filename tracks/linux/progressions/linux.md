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

## Ch. 4 — Control Access to Files
*New this session:*

| Command/Concept | What it does |
|----------------|-------------|
| `chmod Who/What/Which file` | Change permissions (symbolic: u/g/o/a, +/-/=, r/w/x/X) |
| `chmod ### file` | Change permissions (octal: r=4 w=2 x=1, three digits for u/g/o) |
| `chmod -R` | Recursively apply permissions to directory tree |
| `chown user file` | Change file user owner (root only) |
| `chown :group file` | Change file group owner (use colon, not dot) |
| `chown user:group file` | Change both owner and group at once |
| `chgrp group file` | Change group owner only |
| `umask` | Display current permission mask for new files/dirs |
| `umask NNN` | Set umask for current shell session |
| setuid (`u+s`, octal 4) | File runs as file owner; no dir effect |
| setgid (`g+s`, octal 2) | File runs as file group; dir: new files inherit dir's group |
| sticky (`o+t`, octal 1) | Dir: only file owner can delete their own files |
| `chmod 2770 dir` | setgid + rwx for owner/group, none for other |
| `/etc/login.defs` UMASK | System-wide default umask for login shells |
