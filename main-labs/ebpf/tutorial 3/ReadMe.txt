---
# README - eBPF TCP/UDP Counter Lab

This lab demonstrates an eBPF XDP program running on the "firewall" node, which counts the number of incoming TCP and UDP packets. The eBPF program uses a map with two counters: one for TCP packets (index 0) and one for UDP packets (index 1).

## Lab Configuration

- Firewall Node:
  - Runs the eBPF XDP program.
  - Uses the Docker image *kathara/ebpf*.
- pc0 Node:
  - Used to generate test traffic.
  - Contains two scripts: `udp_sender.py` (for UDP packets) and `tcp_sender.py` (for TCP packets).
- Wireshark (optional):
  - Can be attached to monitor network traffic.

## Compiling and Attaching the eBPF Program

1. Compile the eBPF Program:

   Navigate to the home directory on the firewall node and compile the program using the provided Makefile. This will generate an object file (e.g., `firewall.o`).

   Command:  
   `cd /home && make`

2. Attach the eBPF Program:

   Attach the compiled program to the network interface (e.g., `eth0`) with:  
   `ip link set dev eth0 xdp obj firewall.o sec xdp`

   After attaching, verify that the eBPF program is active by running:  
   - `bpftool prog show`  
   - `bpftool net`

## Monitoring the Packet Count Map

1. View Initial Map Values:

   Identify the map ID from the output of `bpftool prog show` and then dump the map contents:  
   `bpftool map dump id <xx>`  
   Replace `<xx>` with the actual map ID. Initially, both counters should be zero.

2. Generate Traffic:

   From the pc0 node, run the sender scripts in the 'shared' folder to generate test traffic:
   - For UDP packets:  
     `python3 udp_sender.py`
   - For TCP packets:  
     `python3 tcp_sender.py`

3. View Updated Map Values:

   Run the same command to dump the map contents:  
   `bpftool map dump id <xx>`  
   The counters for TCP and UDP should now reflect the number of packets received.

4. Optional - Disable the eBPF Program:

   To disable the eBPF program, run:  
   `ip link set dev eth0 xdp off`

## Additional Information

For any further details or troubleshooting, please refer to the README in the parent folder, which contains comprehensive instructions on eBPF commands and program usage. 

It is recommended to read that document before proceeding.

Happy testing and learning!
---