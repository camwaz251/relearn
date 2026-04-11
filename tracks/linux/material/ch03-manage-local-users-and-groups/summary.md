# Chapter 3 — Manage Local Users and Groups

## User Types

| Type | UID Range | Purpose |
|------|-----------|---------|
| Superuser | 0 | `root` — full system access |
| System (static) | 1–200 | Statically assigned to system processes |
| System (dynamic) | 201–999 | Dynamically assigned; no file ownership |
| Regular | 1000+ | Normal unprivileged users |

## `/etc/passwd` Format

```
username:x:UID:GID:comment:home_dir:shell
```

Seven colon-separated fields:
- **username** — login name
- **x** — password placeholder (actual hash in `/etc/shadow`)
- **UID** — numeric user ID
- **GID** — primary group ID
- **comment** — real name / description (GECOS)
- **home_dir** — home directory path
- **shell** — login shell (`/bin/bash`, `/sbin/nologin`, etc.)

## Groups

A group is a collection of users that share access to files/resources.

### `/etc/group` Format

```
groupname:x:GID:user1,user2,user3
```

Four fields: name, password placeholder, GID, comma-separated member list.

### Primary vs Supplementary Groups

- **Primary group** — listed by GID in `/etc/passwd`. Owns new files the user creates. One per user.
- **Supplementary groups** — listed in `/etc/group`. Grant additional file access. A user can have many.
- User Private Group (UPG) — by default, a new user gets a group with the same name as the username.

### Key Commands

```bash
id [username]          # show UID, GID, all groups
id -G username         # show supplementary group GIDs
```

---

## Gaining Superuser Access

### `su` vs `su -` vs `sudo`

| | `su` | `su -` | `sudo` |
|---|---|---|---|
| Become new user | Yes | Yes | Per escalated command |
| Environment | Current user's | New user's (login shell) | Current user's |
| Password required | New user's | New user's | Current user's |
| Privileges | Same as new user | Same as new user | Defined by config |
| Activity logged | `su` command only | `su` command only | Per escalated command |

```bash
su username            # switch user, non-login shell (keeps env)
su - username          # switch user, login shell (full env reset)
su -                   # switch to root, login shell
sudo command           # run single command as root
sudo -i                # interactive root login shell
sudo -s                # interactive root shell (no login scripts)
sudo su -              # combine: sudo auth, then login shell as root
```

### Configure sudo

- Config file: `/etc/sudoers` — edit ONLY with `visudo`
- Drop-in directory: `/etc/sudoers.d/` — add per-user/group files here
- `wheel` group members get full sudo by default (RHEL 7+)

#### Sudoers syntax

```
user    HOST=(RUNAS)    COMMANDS
```

Examples:
```
%wheel      ALL=(ALL:ALL)    ALL              # wheel group: full access
user01      ALL=(ALL)        ALL              # single user: full access
%games      ALL=(operator)   /bin/id          # group: one command as operator
ansible     ALL=(ALL)        NOPASSWD: ALL    # no password required
```

- `%` prefix = group
- `NOPASSWD:` = skip password prompt (use with SSH key auth)

#### Sudo logging

All sudo commands logged to `/var/log/secure`.

---

## Manage Local User Accounts

### Create Users

```bash
useradd username              # create user, home dir, private group
useradd -u 1500 username      # specify UID
useradd -s /sbin/nologin svc  # system service account (no login)
```

- Default settings come from `/etc/login.defs`
- First free UID >= 1000 assigned (unless `-u` specified)
- No password set until `passwd` is run — user cannot log in

### Modify Users (`usermod`)

| Option | Effect |
|--------|--------|
| `-a, --append` | Use with `-G` to append (not replace) supplementary groups |
| `-c, --comment` | Set GECOS/comment field |
| `-d, --home` | Set home directory |
| `-g, --gid` | Set primary group |
| `-G, --groups` | Set supplementary groups (replaces all unless `-a` used) |
| `-L, --lock` | Lock account (prepends `!` to password hash) |
| `-U, --unlock` | Unlock account |
| `-m, --move-home` | Move home dir contents (use with `-d`) |
| `-s, --shell` | Set login shell |

```bash
usermod -c "Full Name" username       # set comment
usermod -aG wheel username            # add to wheel (keep existing groups)
usermod -L username                   # lock account
usermod -U username                   # unlock account
usermod -d /new/home -m username      # move home directory
```

### Delete Users

```bash
userdel username              # remove from /etc/passwd, keep home dir
userdel -r username           # remove user AND home directory
```

**Warning:** Without `-r`, orphaned files retain the old UID. If a new user gets that UID, they inherit the files.

### Set Passwords

```bash
passwd username               # set/change password (as root)
passwd                        # change own password
```

---

## Manage Local Group Accounts

### Create Groups

```bash
groupadd groupname            # create group (next available GID)
groupadd -g 30000 groupname   # specify GID
groupadd -r sysgroup          # create system group (GID < 1000)
```

### Modify Groups

```bash
groupmod -n newname oldname   # rename group
groupmod -g 20000 groupname   # change GID
```

### Delete Groups

```bash
groupdel groupname            # delete group
```

Cannot delete a group if it is any user's primary group.

### Change Group Membership

```bash
usermod -g groupname username       # change primary group
usermod -aG group1,group2 username  # add supplementary groups (append)
usermod -G group1 username          # set supplementary groups (REPLACES all)
```

**Critical:** Always use `-aG` (append) unless you intend to replace all supplementary groups.

### Temporarily Switch Primary Group

```bash
newgrp groupname              # switch primary group for current shell
```

New files created in this shell session will be owned by the new primary group. Resets on logout.

---

## Manage User Passwords

### `/etc/shadow` Format

```
username:password_hash:lastchange:min:max:warn:inactive:expire:reserved
```

| Field | Meaning |
|-------|---------|
| `username` | Login name |
| `password_hash` | Encrypted password (`!!` = no password set, `!` prefix = locked) |
| `lastchange` | Days since epoch of last password change |
| `min` | Minimum days between password changes |
| `max` | Maximum days before password must be changed |
| `warn` | Days before expiry to warn user |
| `inactive` | Days after expiry before account is locked |
| `expire` | Account expiration date (days since epoch) |

### Password Aging with `chage`

```bash
chage -l username                    # list password aging info
chage -m 0 -M 90 -W 7 -I 14 user   # min=0, max=90, warn=7, inactive=14
chage -d 0 username                  # force password change on next login
chage -E 2025-12-31 username         # set account expiration date
chage -E -1 username                 # remove account expiration
```

| `chage` option | Field |
|----------------|-------|
| `-m` | Minimum days between changes |
| `-M` | Maximum days before change required |
| `-W` | Warning days before expiry |
| `-I` | Inactive days after expiry |
| `-E` | Account expiration date (YYYY-MM-DD) |
| `-d` | Date of last password change (0 = force change) |
| `-l` | List current aging settings |

### Lock/Unlock Accounts

```bash
usermod -L username           # lock (adds ! to /etc/shadow hash)
usermod -U username           # unlock
passwd -l username            # lock (alternative)
passwd -u username            # unlock (alternative)
```

### `nologin` Shell

Set `/sbin/nologin` as shell to prevent interactive login while still allowing the account to own files/processes:

```bash
usermod -s /sbin/nologin username
```
