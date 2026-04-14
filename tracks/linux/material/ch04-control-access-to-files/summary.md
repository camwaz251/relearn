# Chapter 4 — Control Access to Files

## Reading Permission Strings

`ls -l` shows a 10-character string:

```
-rwxr-x---
^   ^  ^  ^
|   |  |  other
|   |  group
|   user (owner)
file type (- file, d dir, l symlink)
```

Each triplet: `r` (read=4), `w` (write=2), `x` (execute=1), `-` (none).

- **File**: r=read content, w=modify content, x=run as program
- **Directory**: r=list contents, w=create/delete files inside, x=enter/traverse

---

## chmod — Change Permissions

### Symbolic Method

```
chmod Who/What/Which file|directory
```

| Who | Meaning         |
|-----|-----------------|
| `u` | user (owner)    |
| `g` | group           |
| `o` | other           |
| `a` | all (u+g+o)     |

| What | Meaning        |
|------|----------------|
| `+`  | add permission |
| `-`  | remove permission |
| `=`  | set exactly    |

| Which | Meaning        |
|-------|----------------|
| `r`   | read           |
| `w`   | write          |
| `x`   | execute        |
| `X`   | execute only if dir, or if any execute bit already set |

```
chmod go-rw document.pdf     # remove read+write from group and other
chmod a+x myscript.sh        # add execute for everyone
chmod u=rw,g=r,o= file.txt   # set exactly: owner rw, group r, other none
chmod -R g+rwX /data/shared  # recursive: group gets rwx on dirs, rw on files
```

> `X` (capital) is safe for recursive operations — it won't make plain files executable.

### Octal Method

```
chmod ### file|directory
```

Each digit is the sum of bits for that class (u, g, o):

| Bit  | Value |
|------|-------|
| read | 4     |
| write | 2   |
| execute | 1 |

```
chmod 644 file.txt    # rw-r--r--  (owner rw, group r, other r)
chmod 750 scriptdir   # rwxr-x---  (owner rwx, group rx, other none)
chmod 600 private.key # rw-------  (owner rw only)
chmod 755 /usr/bin/prog # rwxr-xr-x
```

---

## chown — Change Ownership

Only **root** can change the user owner. Owner or root can change group ownership.

```
chown user file            # change user owner
chown :group file          # change group only (colon prefix, not dot)
chown user:group file      # change both at once
chown -R user /dir         # recursive ownership change
```

> Do not use `chown owner.group` (dot syntax) — Red Hat discourages it because a period is a valid character in usernames.

## chgrp — Change Group Only

```
chgrp group file           # equivalent to chown :group file
```

---

## Special Permissions

A fourth type beyond ugo/rwx, set as a preceding digit in octal notation.

| Permission | Symbolic | Octal | Effect on Files | Effect on Directories |
|-----------|----------|-------|-----------------|----------------------|
| setuid | `u+s` | 4 | Runs as file owner, not caller | No effect |
| setgid | `g+s` | 2 | Runs as file group | New files inherit dir's group |
| sticky | `o+t` | 1 | No effect | Only file owner can delete their files |

**Identifying in `ls -l`:**
- setuid: `s` or `S` in owner's execute slot (`-rwsr-xr-x`)
- setgid: `s` or `S` in group's execute slot (`-rwxr-sr-x`)
- sticky: `t` or `T` in other's execute slot (`drwxrwxrwt`)
- Uppercase means the underlying execute bit is NOT set

**Setting special permissions:**

```
chmod g+s /data/shared      # symbolic: add setgid to directory
chmod o+t /tmp              # symbolic: add sticky bit
chmod u-s /usr/bin/myprog   # symbolic: remove setuid

chmod 2770 /data/shared     # octal: setgid(2) + rwx(7) owner, rwx(7) group, none(0) other
chmod 1777 /tmp             # octal: sticky(1) + rwxrwxrwx
chmod 4755 /usr/bin/prog    # octal: setuid(4) + rwxr-xr-x
chmod 0770 /data/shared     # explicitly clear special bits + set 770
```

**Why they matter:**
- **setuid** is how `passwd` writes to `/etc/shadow` as root even when run by a regular user
- **setgid on a directory** is the standard pattern for group collaboration directories — every file created inherits the group, so members always have access
- **sticky** is why `/tmp` lets everyone create files but not delete each other's files

---

## Default Permissions (umask)

Two factors set initial permissions when a file is created:
1. **Starting value**: files start at `0666`, directories at `0777` (execute is never given to files by default)
2. **umask**: clears bits from the starting value

```
umask          # display current umask
umask 027      # set umask for current shell session
```

**How umask works** — bits set in the umask are cleared from new files:

```
File:       0666  (rw-rw-rw-)
umask 0022: 0022  (----w--w-)
Result:     0644  (rw-r--r--)

Directory:  0777  (rwxrwxrwx)
umask 0022: 0022  (----w--w-)
Result:     0755  (rwxr-xr-x)
```

Common umask values:

| umask | Files | Directories | Use case |
|-------|-------|-------------|---------|
| 0022 | 644 | 755 | Default — group/other read-only |
| 0027 | 640 | 750 | Group read, other no access |
| 0007 | 660 | 770 | Group full access, other no access |
| 0077 | 600 | 700 | Owner only |

**Where umask is configured:**

```
/etc/login.defs         # UMASK line — applies to login shells (system-wide)
/etc/bashrc             # interactive non-login shells
~/.bash_profile         # user override for login shells
~/.bashrc               # user override for non-login shells
/etc/profile.d/*.sh     # drop-in scripts (e.g., local-umask.sh)
```

> umask changes persist only for the current shell unless written to a config file.
