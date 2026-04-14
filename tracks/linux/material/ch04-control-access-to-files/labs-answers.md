# Chapter 4 — Lab Answers

### Lab 1: Control Access to Files

Run `lab start perms-review` on workstation before starting.

1. SSH to serverb and switch to root.

```
ssh student@serverb
sudo -i
```

2. Create `/home/techdocs`.

```
mkdir /home/techdocs
```

3. Change group ownership to `techdocs`.

```
chown :techdocs /home/techdocs
```

4. Check permissions, then try to create a file as `tech1`. It fails because the `techdocs`
   group doesn't have write permission yet.

```
ls -ld /home/techdocs
su - tech1
touch /home/techdocs/techdoc1.txt    # Permission denied
ls -ld /home/techdocs/               # drwxr-xr-x — group has no write
exit
```

5. Set setgid + rwx for owner and group, no access for other.

```
chmod 2770 /home/techdocs
ls -ld /home/techdocs                # drwxrws---
```

6. As `tech1`, create a file. The group owner is `techdocs` automatically (setgid).

```
su - tech1
touch /home/techdocs/techdoc1.txt
echo "This is the first tech doc." > /home/techdocs/techdoc1.txt
ls -l /home/techdocs/techdoc1.txt    # group owner = techdocs
exit
```

7. As `tech2`, read `tech1`'s file and create a new one.

```
su - tech2
cd /home/techdocs
cat techdoc1.txt                     # succeeds
touch /home/techdocs/techdoc2.txt
ls -l                                # both files visible, both owned by techdocs
exit
```

8. As `database1` (not in `techdocs`), confirm access is denied.

```
su - database1
cat /home/techdocs/techdoc1.txt      # Permission denied
exit
```

9. Set system-wide UMASK to 007 in `/etc/login.defs`.

```
vim /etc/login.defs
# find UMASK line and set:
UMASK   007
```

10. Log out completely and SSH back in as `student`. Verify the umask.

```
exit                                 # exit root
exit                                 # exit serverb
ssh student@serverb
umask                                # should show 0007
exit
```

On workstation, grade then clean up:

```
lab grade perms-review
lab finish perms-review
```
