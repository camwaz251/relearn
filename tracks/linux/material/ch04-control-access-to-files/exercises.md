# Chapter 4 — Exercises

### Exercise 1
A file `report.pdf` currently has permissions `rw-rw-rw-`. You want to remove read and
write access for group and other without touching the owner's permissions.
Write the symbolic `chmod` command.

### Exercise 2
A shell script `deploy.sh` has permissions `rw-r--r--`. You want to add execute permission
for everyone. Write the symbolic `chmod` command.

### Exercise 3
A directory `/data/project` contains a mix of scripts and data files. You need to give the
`devs` group read, write, and execute access to the directory and all its contents — but
you must not make the plain data files executable. Write the `chmod` command (use `-R`).

### Exercise 4
Set the following permissions on `app.conf` using the octal method:
- Owner: read + write
- Group: read only
- Other: no access

### Exercise 5
Set permissions on `webapp/` directory using the octal method:
- Owner: read + write + execute
- Group: read + execute
- Other: no access

### Exercise 6
The following `ls -l` output shows three files. Identify what special permission each has
and explain what it does:

```
-rwsr-xr-x. 1 root root  35504 Jul 16 /usr/bin/passwd
drwxr-sr-x. 3 root systemd-journal 60 May 18 /run/log/journal
drwxrwxrwt. 39 root root 4096 Feb 8 /tmp
```

### Exercise 7
A user's umask is `0027`. They create a regular file and a directory.
What are the resulting permissions (symbolic and octal) for each?

### Exercise 8
You manage a shared directory `/home/engineering`. You want files created inside it to
automatically be owned by the `engineers` group (regardless of which group member creates
them). What command configures this?

---

## Answers

### Exercise 1
```
chmod go-rw report.pdf
```

### Exercise 2
```
chmod a+x deploy.sh
```

### Exercise 3
```
chmod -R g+rwX /data/project
```
Using capital `X` sets execute on directories and files that already have execute set,
but not on plain data files.

### Exercise 4
Owner rw = 6, Group r = 4, Other none = 0:
```
chmod 640 app.conf
```

### Exercise 5
Owner rwx = 7, Group rx = 5, Other none = 0:
```
chmod 750 webapp/
```

### Exercise 6
- `/usr/bin/passwd`: `s` in owner execute slot = **setuid**. Runs as root (file owner)
  regardless of who executes it — this is how it can write to `/etc/shadow`.
- `/run/log/journal`: `s` in group execute slot = **setgid on a directory**. Files created
  inside inherit the `systemd-journal` group owner.
- `/tmp`: `t` in other execute slot = **sticky bit on a directory**. Everyone can create
  files, but only the file owner (or root) can delete them.

### Exercise 7
Starting permissions: file=0666, dir=0777
Umask 0027 clears bits: ----w-rwx

```
File:      0666 - 0027 = 0640  →  rw-r-----
Directory: 0777 - 0027 = 0750  →  rwxr-x---
```

### Exercise 8
```
chmod g+s /home/engineering
```
setgid on a directory causes new files to inherit the directory's group owner.
