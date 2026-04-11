# Chapter 3 — Exercises

## Exercise 1: Gain Superuser Access

Practice switching to the `root` account and running commands as `root`.

**Outcomes:**
- Use `sudo` to switch to `root` without knowing the superuser password
- Explain how `su` and `su -` affect the shell environment
- Use `sudo` to run commands as `root`

**Before You Begin:**
```
lab start users-superuser
```

### Instructions

1. From `workstation`, SSH to `servera` as `student`.

2. Explore the shell environment. Run `id`, `pwd`, `echo $HOME`, and `echo $PATH`.

3. Switch to `root` in a **non-login shell**: run `sudo su`. Check `id`, `pwd`, `echo $HOME`, and `echo $PATH`. Note the differences. Exit back to `student`.

4. Switch to `root` in a **login shell**: run `sudo su -`. Check `id`, `pwd`, `echo $HOME`, and `echo $PATH`. Compare with step 3. Exit back to `student`.

5. Verify that the `operator1` user can run any command with `sudo`:
   ```
   sudo cat /etc/sudoers.d/operator1
   ```

6. Switch to `operator1` (password: `redhat`). Perform these tasks using `sudo` (do NOT use `sudo su` or `sudo su -`):
   - Try to view `/var/log/messages` without `sudo` — should fail.
   - View `/var/log/messages` with `sudo` — should succeed.
   - Try to copy `/etc/motd` to `/etc/motdOLD` without `sudo` — should fail.
   - Copy with `sudo` — should succeed.
   - Try to delete `/etc/motdOLD` without `sudo` — should fail.
   - Delete with `sudo` — should succeed.

7. Return to `workstation`.

**Finish:**
```
lab finish users-superuser
```

---

## Exercise 2: Manage Local User Accounts

Create several users and set passwords.

**Outcomes:**
- Configure a Linux system with additional user accounts

**Before You Begin:**
```
lab start users-user
```

### Instructions

1. From `workstation`, SSH to `servera` as `student`, then switch to `root` with `sudo -i`.

2. Create `operator1` and confirm it exists:
   ```
   useradd operator1
   tail /etc/passwd
   ```

3. Set the password for `operator1` to `redhat`:
   ```
   passwd operator1
   ```

4. Create `operator2` and `operator3`. Set both passwords to `redhat`.

5. Update the comments for `operator1` and `operator2`:
   ```
   usermod -c "Operator One" operator1
   usermod -c "Operator Two" operator2
   ```
   Verify with `tail /etc/passwd`.

6. Delete `operator3` along with their home directory:
   ```
   userdel -r operator3
   ```
   Confirm the user and home directory are gone.

7. Exit root, log off `servera`, return to `workstation`.

**Finish:**
```
lab finish users-user
```

---

## Exercise 3: Manage Local Group Accounts

Create groups, use them as supplementary groups, and configure `sudo` access for a group.

**Outcomes:**
- Create groups and use them as supplementary groups
- Configure `sudo` access for a group

**Before You Begin:**
```
lab start users-group
```

### Instructions

1. From `workstation`, SSH to `servera` as `student`, then switch to `root` with `sudo -i`.

2. Create the `operators` supplementary group with GID 30000:
   ```
   groupadd -g 30000 operators
   ```

3. Create the `admin` supplementary group (auto GID):
   ```
   groupadd admin
   ```

4. Verify both groups exist:
   ```
   tail /etc/group
   ```

5. Add `operator1`, `operator2`, and `operator3` to the `operators` group:
   ```
   usermod -aG operators operator1
   usermod -aG operators operator2
   usermod -aG operators operator3
   ```
   Confirm with `id operator1`, etc.

6. Add `sysadmin1`, `sysadmin2`, and `sysadmin3` to the `admin` group:
   ```
   usermod -aG admin sysadmin1
   usermod -aG admin sysadmin2
   usermod -aG admin sysadmin3
   ```

7. Verify supplementary group memberships:
   ```
   tail /etc/group
   ```

8. Grant full `sudo` access to the `admin` group:
   ```
   echo "%admin ALL=(ALL) ALL" >> /etc/sudoers.d/admin
   ```

9. Switch to `sysadmin1` and verify `sudo` works:
   ```
   su - sysadmin1
   sudo cat /etc/shadow
   ```

10. Return to `workstation`.

**Finish:**
```
lab finish users-group
```

---

## Exercise 4: Manage User Passwords

Configure password policies and expiration.

**Outcomes:**
- Set password policies for users
- Force a password change at next login
- Set account expiration

**Before You Begin:**
```
lab start users-password
```

### Instructions

1. From `workstation`, SSH to `servera` as `student`, then switch to `root` with `sudo -i`.

2. Lock the `operator1` account and verify:
   ```
   usermod -L operator1
   ```
   Try to switch to `operator1` — authentication should fail.

3. Unlock `operator1`:
   ```
   usermod -U operator1
   ```

4. Change the password policy for `operator1`: minimum age 10 days, maximum age 90 days, warning 7 days, inactive 14 days:
   ```
   chage -m 10 -M 90 -W 7 -I 14 operator1
   ```

5. Force `operator1` to change password at next login:
   ```
   chage -d 0 operator1
   ```

6. Set `operator1` account to expire on 2025-12-31:
   ```
   chage -E 2025-12-31 operator1
   ```

7. View the password aging information:
   ```
   chage -l operator1
   ```

8. Set the `/sbin/nologin` shell for a service account:
   ```
   usermod -s /sbin/nologin operator2
   ```

9. Return to `workstation`.

**Finish:**
```
lab finish users-password
```

---

## Answers

### Exercise 1

Key observations:
- `sudo su` (non-login shell): `HOME=/root`, `PATH` is overridden by sudo but not by shell login scripts. `pwd` stays at `/home/student`.
- `sudo su -` (login shell): `HOME=/root`, `PATH` is set by root's login scripts. `pwd` changes to `/root`.
- `operator1`'s sudoers file contains: `operator1 ALL=(ALL) ALL`
- Commands without `sudo` fail with "Permission denied"; commands with `sudo` succeed.

### Exercise 2

After creating users:
```
operator1:x:1002:1002:Operator One:/home/operator1:/bin/bash
operator2:x:1003:1003:Operator Two:/home/operator2:/bin/bash
```
- `operator3` is gone from `/etc/passwd` and `/home` after `userdel -r`.

### Exercise 3

After adding to groups:
```
operators:x:30000:operator1,operator2,operator3
admin:x:30001:sysadmin1,sysadmin2,sysadmin3
```
- `sysadmin1` can run `sudo cat /etc/shadow` because the `admin` group has a sudoers entry.

### Exercise 4

After configuring `operator1`:
```
chage -l operator1
```
Shows:
- Minimum: 10 days
- Maximum: 90 days
- Warning: 7 days
- Inactive: 14 days
- Last password change: password must be changed (forced)
- Account expires: Dec 31, 2025
