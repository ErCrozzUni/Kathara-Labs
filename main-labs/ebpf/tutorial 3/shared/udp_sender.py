#!/usr/bin/env python3

from scapy.all import *
import time

# Parametri da personalizzare
DEST_IP = "192.168.0.2"   # L'IP di destinazione dove è in ascolto l'eBPF
DEST_PORT = 8888          # Porta di destinazione arbitraria
SRC_PORT = 4444           # Porta sorgente arbitraria
INTERVAL = 1              # Invia un pacchetto ogni 4 secondi

def main():
    # Creiamo un singolo pacchetto UDP
    pkt = IP(dst=DEST_IP) / UDP(sport=SRC_PORT, dport=DEST_PORT) / Raw("Test data")

    # Loop infinito: invia un pacchetto ogni INTERVAL secondi
    while True:
        send(pkt, verbose=False)
        print(f"Inviato un pacchetto a {DEST_IP}:{DEST_PORT}")
        time.sleep(INTERVAL)

if __name__ == "__main__":
    main()
