README - Kathara Lab - eBPF Usage
This lab uses a single computer named "firewall" as defined in the lab configuration (lab.conf):

# Firewall eBPF 
firewall[0]="A"
firewall[image]="kathara/ebpf"
firewall[ipv6]="false"

We use a Docker image called kathara/ebpf that includes all the necessary installations for running eBPF programs. 

The provided eBPF program is designed to discard all incoming packets once activated.

To help you understand how to work with eBPF, follow these steps:

Check Initial eBPF Programs
Before compiling or attaching any new eBPF program, run the following commands to inspect the currently loaded eBPF programs:

bpftool prog show
bpftool net
These commands display the active eBPF programs and network hooks currently in use.

Compile the eBPF Program
Navigate to the home directory and compile the program using the Makefile. You may modify the program if desired.

Command:
cd /home && make

This compiles the eBPF program, generating an object file (named firewall.o) ready for attachment.

Attach the eBPF Program
Attach the compiled eBPF program to the network interface (eth0 in this lab) with the following command:

ip link set dev eth0 xdp obj firewall.o sec xdp

After attaching, run bpftool prog show and bpftool net again to verify that the eBPF program is active on the interface.

Disable the eBPF Program
To disable the attached eBPF program, execute:

ip link set dev eth0 xdp off

For any doubts or further questions, please refer to the README in the parent folder. 

It contains comprehensive commands and explanations regarding eBPF programs, which should be read first.

Happy testing and learning!