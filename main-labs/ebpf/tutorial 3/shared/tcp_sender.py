#!/usr/bin/env python3

from scapy.all import *
import time

# Parameters (customize as needed)
DEST_IP = "192.168.0.2"   # Firewall static IP address
DEST_PORT = 23456         # Arbitrary destination TCP port
SRC_PORT = 4444           # Arbitrary source port
INTERVAL = 1              # Send a packet every 4 seconds

def main():
    # Create a TCP packet with the RST flag to prevent session establishment
    pkt = IP(dst=DEST_IP) / TCP(sport=SRC_PORT, dport=DEST_PORT, flags="R") / Raw("Test TCP data")
    while True:
        send(pkt, verbose=False)
        print(f"Sent a TCP packet (RST) to {DEST_IP}:{DEST_PORT}")
        time.sleep(INTERVAL)

if __name__ == "__main__":
    main()
