#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

// Definizione di una mappa di tipo ARRAY con una sola entry
// La mappa ha chiave di tipo int e valore di tipo int
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __uint(max_entries, 1);
    __type(key, int);
    __type(value, int);
} counter_map SEC(".maps");

// Funzione XDP che viene eseguita per ogni pacchetto in ingresso
SEC("xdp")
int xdp_counter(struct xdp_md *ctx) {
    int key = 0;
    int *counter;

    // Recupera il puntatore al contatore dalla mappa
    counter = bpf_map_lookup_elem(&counter_map, &key);
    if (counter) {
        // Incrementa il contatore
        __sync_fetch_and_add(counter, 1);
    }

    // Passa il pacchetto alla pila di rete
    return XDP_PASS;
}

// Licenza necessaria per il caricamento del programma
char _license[] SEC("license") = "GPL";
