# Chapter 3 — Labs

## Lab: Manage Local Users and Groups

Configure users, groups, passwords, and sudo access on a system.

**Objectives:**
- Create and manage user accounts
- Create and manage groups and group memberships
- Configure password policies
- Configure superuser access

**Before You Begin:**

As `student` on `workstation`:
```
lab start users-review
```

### Steps

1. Set a password policy on `servera` that requires `operator1` to change their password every 90 days. The minimum time between password changes is 0. The warning period is 14 days before expiry.

2. Force `operator1` to change their password on the next login.

3. Make `operator1` a member of the `operators` group (supplementary).

4. Create a new group `managers` with GID 35000 on `servera`.

5. Create a new user `manager1` with the `managers` group as a supplementary group.

6. Set `manager1`'s password to `redhat`.

7. Configure `managers` group to have full `sudo` access by creating an appropriate file in `/etc/sudoers.d/`.

8. Verify `manager1` can run administrative commands with `sudo`.

### Evaluation

Grade your work:
```
lab grade users-review
```

### Finish

```
lab finish users-review
```

*No answers provided — work through on your Red Hat VM.*
