# Chapter 4 — Labs

### Lab 1: Control Access to Files

Set up a shared directory for group collaboration and configure a system-wide default umask.

Run `lab start perms-review` on workstation before starting.

Objectives:
- Create a directory where group members can create, read, and edit files
- Ensure files created inside automatically belong to the group
- Prevent users outside the group from accessing any files
- Set an appropriate default umask system-wide

1. SSH to serverb as student. Switch to root with `sudo -i`.

2. Create the directory `/home/techdocs`.

3. Change the group ownership of `/home/techdocs` to the `techdocs` group.

4. Check the current permissions on `/home/techdocs`. Switch to `tech1` (in the `techdocs`
   group) and attempt to create a file inside `/home/techdocs`. Note what happens and why.

5. As root, set permissions on `/home/techdocs`: setgid bit enabled, rwx for owner and
   group, no permissions for other.

6. Switch back to `tech1`. Create a file inside `/home/techdocs` and verify the file's
   group owner is `techdocs`, not `tech1`'s primary group.

7. Switch to `tech2` (also in `techdocs`). Verify `tech2` can read `tech1`'s file and
   create their own file in `/home/techdocs`.

8. Switch to `database1` (not in `techdocs`). Attempt to read a file in `/home/techdocs`.
   Verify access is denied.

9. As root, modify `/etc/login.defs` to set UMASK to `007`.

10. Log out and back in as `student`. Verify the new umask with `umask`.

When done, run these on workstation as student:

```
lab grade perms-review
lab finish perms-review
```

*No answers provided — work through on your Red Hat VM.*
