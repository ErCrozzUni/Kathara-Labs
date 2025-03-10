---
# README - eBPF Firewall Lab

In this lab, the firewall runs an eBPF program that counts the number of incoming packets. 

For example, when you send a ping from pc0, the eBPF program will increment its counter.

To work with the eBPF program and monitor its behavior, follow these steps:

---

## Compiling and Attaching the eBPF Program

1. Compile the eBPF Program
   Navigate to the home directory and compile the program using the provided Makefile.
   You can modify the source code if desired.  
   Command:  
   `cd /home && make`  
   This will generate the object file firewall.o.

2. Attach the eBPF Program
   Attach the compiled program to the network interface (eth0) with:  
   `ip link set dev eth0 xdp obj firewall.o sec xdp`  
   After attaching, run the following commands to verify that the eBPF program is active:  
   - `bpftool prog show`  
   - `bpftool net`  
   These commands will display the active eBPF programs and associated maps.

3. View the Packet Count Map
   Identify the map ID from the output of `bpftool prog show`, then run:  
   `bpftool map dump id <xx>`  
   Replace `<xx>` with the actual map ID to view the current packet count.

4. Ping the Firewall from Pc0  
   From the pc0 node, send a ping to the firewall to generate network traffic.  
   Example command:  
   `ping <firewall_IP>`

5. View the Updated Packet Count Map  
   Run the same command as in step 3 to view the updated map reflecting the new packet count:  
   `bpftool map dump id <xx>`

6. Disable the eBPF Program (Optional)  
   To disable the attached program, run:  
   `ip link set dev eth0 xdp off`

---

## Additional Lab Information

If desired, you can also attach the Wireshark container to the network interface to monitor network traffic and gain further insight into what is happening on the network.

For any further details or questions, please refer to the README in the parent folder, which contains comprehensive instructions on eBPF commands and program usage. 

Reading that document is recommended before proceeding.

Happy testing and learning!
---