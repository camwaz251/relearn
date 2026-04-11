# Linux Track — Claude Instructions

The repo-root `CLAUDE.md` loads automatically alongside this file — it holds the
general project rules. Also update `../../progress.md` after every session.

## Source
Red Hat RHCSA book — `knowledge/RH199_RHCSA_Rapid_Track_en_9.3.pdf`.

## Background
User is prepping for RHCSA certification. Has the Red Hat book. Uses a Red Hat VM for hands-on work.

---

## Directory Structure

```
knowledge/          — source PDF + index.md (chapter status tracker)
material/           — lesson content per chapter (summary.md, exercises.md, labs.md)
progressions/       — skill/concept progression tracking
```

---

## Workflow Per Chapter

1. User says which chapter.
2. **Enter plan mode first.** Read the chapter from the Red Hat PDF, then present a plan: what topics will be covered, how the summary/exercises/labs will be structured, and which RHCSA objectives this chapter maps to. User confirms or adjusts before you write anything.
3. Write three files in `material/chXX-<name>/`:
   - `summary.md` — clean, stripped-down topic summary
   - `exercises.md` — reformatted exercises from the book, answers at the end
   - `labs.md` — reformatted labs, NO answers (intentional — for practice)
4. Append new commands/concepts to `progressions/linux.md`.
5. User uses the Red Hat VM for actual hands-on work.

---

## summary.md Format

- Just the concepts, commands, and config.
- No filler. No padding. Short sentences.
- Scannable: use headers, bullet points, and code blocks.
- Format for commands:
  ```
  command [options] <args>    # what it does
  ```

---

## exercises.md Format

```markdown
# Chapter X — Exercises

### Exercise 1
<clean restatement of the exercise>

### Exercise 2
...

---

## Answers

### Exercise 1
<answer>
```

---

## labs.md Format

```markdown
# Chapter X — Labs

### Lab 1
<clean restatement of the lab>

**Objectives:**
- ...

**Steps:**
1. ...

*No answers provided — work through on your Red Hat VM.*
```

---

## RHCSA Exam Study Points

`rhcsa-objectives.md` at the track root lists all official exam objectives.
When a chapter covers one of those objectives, note it in `knowledge/index.md`.

Candidates must be able to accomplish these without assistance:

### Understand and use essential tools
- Access a shell prompt and issue commands with correct syntax
- Use input-output redirection (>, >>, |, 2>, etc.)
- Use grep and regular expressions to analyze text
- Access remote systems using SSH
- Log in and switch users in multiuser targets
- Archive, compress, unpack, and uncompress files using tar, gzip, and bzip2
- Create and edit text files
- Create, delete, copy, and move files and directories
- Create hard and soft links
- List, set, and change standard ugo/rwx permissions
- Locate, read, and use system documentation including man, info, and files in /usr/share/doc

### Manage software
- Configure access to RPM repositories
- Install and remove RPM software packages
- Configure access to Flatpak repositories
- Install and remove Flatpak software packages
- Log in and switch users in multiuser targets

### Create simple shell scripts
- Conditionally execute code (use of: if, test, [], etc.)
- Use looping constructs (for, etc.) to process file, command line input
- Process script inputs ($1, $2, etc.)
- Processing output of shell commands within a script

### Operate running systems
- Boot, reboot, and shut down a system normally
- Boot systems into different targets manually
- Interrupt the boot process in order to gain access to a system
- Identify CPU/memory intensive processes and kill processes
- Adjust process scheduling
- Manage tuning profiles
- Locate and interpret system log files and journals
- Preserve system journals
- Start, stop, and check the status of network services
- Securely transfer files between systems

### Configure local storage
- List, create, delete partitions on MBR and GPT disks
- Create and remove physical volumes
- Assign physical volumes to volume groups
- Create and delete logical volumes
- Configure systems to mount file systems at boot by UUID or label
- Add new partitions and logical volumes, and swap to a system non-destructively

### Create and configure file systems
- Create, mount, unmount, and use VFAT, ext4, and xfs file systems
- Mount and unmount network file systems using NFS
- Configure autofs
- Extend existing logical volumes
- Diagnose and correct file permission problems

### Deploy, configure, and maintain systems
- Schedule tasks using at and cron
- Start and stop services and configure services to start automatically at boot
- Configure systems to boot into a specific target automatically
- Configure time service clients
- Install and update software packages from Red Hat CDN, a remote repository, or from the local file system
- Modify the system bootloader

### Manage basic networking
- Configure IPv4 and IPv6 addresses
- Configure hostname resolution
- Configure network services to start automatically at boot
- Restrict network access using firewalld and firewall-cmd

### Manage users and groups
- Create, delete, and modify local user accounts
- Change passwords and adjust password aging for local user accounts
- Create, delete, and modify local groups and group memberships
- Configure superuser access

### Manage security
- Configure firewall settings using firewall-cmd/firewalld
- Manage default file permissions
- Configure key-based authentication for SSH
- Set enforcing and permissive modes for SELinux
- List and identify SELinux file and process context
- Restore default file contexts
- Manage SELinux port labels
- Use boolean settings to modify system SELinux settings

---

## Progressions (`progressions/`)

### `linux.md`
- Tracks commands and concepts introduced per chapter
- Quick reference so user knows what tools they have so far
- Append each session, never re-list already-covered commands

Format (appended each session):
```
## Ch. X — <Chapter Name>
*New this session:*

| Command/Concept | What it does |
|----------------|-------------|
| `cmd`          | Description |
```

---

## Rules
- No answers in `labs.md` — ever.
- Answers go at the END of `exercises.md` as a separate section (so user can attempt first).
- Keep summaries tight. If a concept needs a paragraph, that's the max.
- Update `../../progress.md` after each session.
- Update `knowledge/index.md` — mark the chapter done.
- Append commands to `progressions/linux.md` every session — no exceptions.
