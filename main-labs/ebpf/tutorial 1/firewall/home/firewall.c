#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

// Funzione XDP che viene eseguita per ogni pacchetto in ingresso
SEC("xdp")
int xdp_counter(struct xdp_md *ctx) {
    return XDP_DROP;
}

// Licenza necessaria per il caricamento del programma
char _license[] SEC("license") = "GPL";
