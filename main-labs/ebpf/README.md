---

# README - eBPF Lab

Welcome to the eBPF Lab!

This repository contains examples and basic commands for working with eBPF programs in a lab environment set up with Kathara. 

Here you will find instructions for compiling, attaching, and verifying eBPF programs, along with useful details on writing them.

---

## Introduction

**eBPF (Extended Berkeley Packet Filter)** is a runtime environment within the Linux kernel that allows you to load and execute custom code safely and dynamically. 

With eBPF, you can modify kernel behavior without needing to replace or reboot it. 

The built-in verification process and Just-In-Time (JIT) compilation ensure that eBPF code runs with near-native performance while maintaining system security.

---

## Commands for Managing eBPF Programs

### 1. Compiling the eBPF Program

- **Compilation using clang:**

  clang -O2 -target bpf -c xdp_drop.c -o xdp_drop.o

  This command compiles the source file `xdp_drop.c`, generating an object file compatible with eBPF.

- **Compilation using Make:**

  make filename

  This command uses a Makefile to automate the compilation process.

### 2. Attaching the eBPF Program to a Network Interface

- To attach the eBPF program to a specific network interface:

  sudo ip link set dev <interface> xdp obj xdp_drop.o sec xdp

  Replace `<interface>` (e.g., `eth0`) with your network interface name.

### 3. Detaching the eBPF Program from the Network Interface

- To temporarily detach the program:

  sudo ip link set dev <interface> xdp off


### 4. Pinning the eBPF Program to the BPF Filesystem

- To load and pin the program:

  sudo bpftool prog load xdp_drop.o /sys/fs/bpf/my_xdp_prog


### 5. Reattaching the Pinned Program to the Network Interface

- To reattach the pinned program:

  sudo ip link set dev <interface> xdp pinned /sys/fs/bpf/my_xdp_prog


### 6. Removing the Pinned Program from the BPF Filesystem

- To remove the program and free the kernel resources:

  sudo rm /sys/fs/bpf/my_xdp_prog


---

## Commands for Verifying Active eBPF Programs

- **Checking active XDP programs on an interface:**

  sudo ip -details link show dev <interface>

  Look for the `prog/xdp` section in the output.

- **Listing active programs on Cgroups:**

  sudo bpftool cgroup tree


- **Listing eBPF programs on other network hooks (non-XDP):**

  sudo bpftool net


- **Displaying all active programs in the kernel:**

  sudo bpftool prog show


---

## Additional Commands

- **Listing all loaded eBPF programs in the kernel:**

  sudo bpftool prog list


- **Displaying details of a specific eBPF program (by ID, name, or tag):**

  sudo bpftool prog show id/name/tag <ID or program name>


- **Viewing the "translated" instructions of an active eBPF program:**

  sudo bpftool prog dump xlated name <program_name>


---

## Writing eBPF Programs

### General Elements

- **Defining the section:**

  SEC("xdp")

  Specifies the type of eBPF program (e.g., XDP, tracepoint) and the kernel section where it will be activated.

- **Debug print:**

  bpf_printk();

  Used to write log or debug messages to the kernel trace buffer (viewable with `dmesg`).

- **Necessary includes:**

  #include <linux/bpf.h>
  #include <bpf/bpf_helpers.h>

- **Program license declaration:**

  char LICENSE[] SEC("license") = "Dual BSD/GPL";

  Required for the program to be executed within the Linux kernel.

### Writing for XDP

- **Accessing packet metadata:**

  struct xdp_md *ctx;

- **Actions on packets:**

  - **Accept and forward the packet:** `XDP_PASS`
  - **Abort processing:** `XDP_ABORTED`
  - **Drop the packet:** `XDP_DROP`
