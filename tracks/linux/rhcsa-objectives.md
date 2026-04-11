# RHCSA Exam Objectives

Source: Red Hat RHCSA (EX200) official objectives.
Mark each objective `[ ]` not covered or `[x]` covered as sessions complete it.

---

## Understand and Use Essential Tools

- [ ] Access a shell prompt and issue commands with correct syntax
- [ ] Use input-output redirection (`>`, `>>`, `|`, `2>`, etc.)
- [ ] Use grep and regular expressions to analyze text
- [ ] Access remote systems using SSH
- [ ] Log in and switch users in multiuser targets
- [ ] Archive, compress, unpack, and uncompress files using tar, gzip, bzip2
- [ ] Create and edit text files with vim
- [ ] Create, delete, copy, and move files and directories
- [ ] Create hard and soft links
- [ ] List, set, and change standard file permissions
- [ ] Locate, read, and use system documentation (man, info, /usr/share/doc)

---

## Create Simple Shell Scripts

- [ ] Conditionally execute code (if, test, `[]`)
- [ ] Use looping constructs (for, while) to process file, command-line input
- [ ] Process script inputs (`$1`, `$2`, etc.)
- [ ] Process output of shell commands within a script

---

## Operate Running Systems

- [ ] Boot, reboot, and shut down a system normally
- [ ] Boot systems into different targets manually
- [ ] Interrupt the boot process to gain access to a system
- [ ] Identify CPU/memory intensive processes, adjust priority with renice, kill
- [ ] Locate and interpret system log files and journals
- [ ] Preserve system journals
- [ ] Start, stop, and check the status of network services
- [ ] Securely transfer files between systems

---

## Configure Local Storage

- [ ] List, create, delete partitions on MBR and GPT disks
- [ ] Create and remove physical volumes
- [ ] Assign physical volumes to volume groups
- [ ] Create and delete logical volumes
- [ ] Configure systems to mount file systems at boot by UUID or label
- [ ] Add new partitions and logical volumes, swap to a system non-destructively

---

## Create and Configure File Systems

- [ ] Create, mount, unmount, and use vfat, ext4, and xfs file systems
- [ ] Mount and unmount network file systems using NFS
- [ ] Extend existing logical volumes
- [ ] Create and configure set-GID directories for collaboration
- [ ] Diagnose and correct file permission problems

---

## Deploy, Configure, and Maintain Systems

- [ ] Schedule tasks using at and cron
- [ ] Start and stop services and configure them to start automatically at boot
- [ ] Configure systems to boot into a specific target automatically
- [ ] Configure time service clients
- [ ] Install and update software packages from Red Hat Network, a remote repo, or from the local file system
- [ ] Work with package module streams
- [ ] Modify the system bootloader

---

## Manage Basic Networking

- [ ] Configure IPv4 and IPv6 addresses
- [ ] Configure hostname resolution
- [ ] Configure network services to start automatically at boot
- [ ] Restrict network access using firewall-cmd/firewall

---

## Manage Users and Groups

- [x] Create, delete, and modify local user accounts
- [x] Change passwords and adjust password aging for local user accounts
- [x] Create, delete, and modify local groups and group memberships
- [x] Configure superuser access

---

## Manage Security

- [ ] Configure firewall settings using firewall-cmd
- [ ] Manage default file permissions
- [ ] Configure key-based authentication for SSH
- [ ] Set enforcing and permissive modes for SELinux
- [ ] List and identify SELinux file and process context
- [ ] Restore default file contexts
- [ ] Manage SELinux port labels
- [ ] Use boolean settings to modify system SELinux settings
- [ ] Diagnose and address routine SELinux policy violations

---

## Manage Containers

- [ ] Find and retrieve container images from a remote registry
- [ ] Inspect container images
- [ ] Perform container management using commands such as podman and skopeo
- [ ] Build a container from a Containerfile
- [ ] Perform basic container management such as running, starting, stopping, listing
- [ ] Run a service inside a container
- [ ] Configure a container to start automatically as a systemd service
- [ ] Attach persistent storage to a container
