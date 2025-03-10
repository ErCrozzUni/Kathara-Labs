#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <bpf/bpf_helpers.h>

struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __uint(max_entries, 2);
    __type(key, __u32);
    __type(value, __u64);
} pkt_count_map SEC(".maps");

SEC("xdp")
int xdp_count(struct xdp_md *ctx)
{
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;

    // Parse Ethernet header
    struct ethhdr *eth = data;
    if ((void *)eth + sizeof(*eth) > data_end)
        return XDP_PASS;

    // Only process IPv4 packets
    if (eth->h_proto != __constant_htons(ETH_P_IP))
        return XDP_PASS;

    // Parse IP header
    struct iphdr *iph = data + sizeof(*eth);
    if ((void *)iph + sizeof(*iph) > data_end)
        return XDP_PASS;

    __u32 key_tcp = 0;
    __u32 key_udp = 1;
    __u64 *count;

    if (iph->protocol == IPPROTO_TCP) {
        count = bpf_map_lookup_elem(&pkt_count_map, &key_tcp);
        if (count)
            __sync_fetch_and_add(count, 1);
    } else if (iph->protocol == IPPROTO_UDP) {
        count = bpf_map_lookup_elem(&pkt_count_map, &key_udp);
        if (count)
            __sync_fetch_and_add(count, 1);
    }

    return XDP_PASS;
}

char _license[] SEC("license") = "Dual BSD/GPL";
