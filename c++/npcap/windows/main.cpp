// myv2ray.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <pcap.h>
#include <iostream>

void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

int main(int argc, char** argv)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle;
    struct bpf_program fp;
    char filter_exp[] = "port 80";
    bpf_u_int32 net, mask;

    // Find all available network interfaces
    pcap_if_t* alldevs;
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Couldn't find any network devices: " << errbuf << std::endl;
        return 1;
    }

    // Use the first available network interface
    char* dev = alldevs->name;

    // Get the network address and netmask of the interface
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        std::cerr << "Couldn't get netmask for device " << dev << ": " << errbuf << std::endl;
        net = 0;
        mask = 0;
    }

    // Open the network interface for capturing
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        std::cerr << "Couldn't open device " << dev << ": " << errbuf << std::endl;
        return 1;
    }

    // Compile the filter expression
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        std::cerr << "Couldn't parse filter " << filter_exp << ": " << pcap_geterr(handle) << std::endl;
        return 1;
    }

    // Apply the filter expression
    if (pcap_setfilter(handle, &fp) == -1) {
        std::cerr << "Couldn't install filter " << filter_exp << ": " << pcap_geterr(handle) << std::endl;
        return 1;
    }

    // Start capturing packets
    pcap_loop(handle, -1, packet_handler, NULL);

    // Close the capture handle
    pcap_close(handle);

    return 0;
}

void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
    // Process the packet data here
    std::cout<<"packet_handler: "<<header->len<<std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

