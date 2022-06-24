#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include "message.h"
using namespace std;

int main(){
    int sockfd_udp;
    int port_out = 44497;
    // create udp socket
    sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_udp == -1){
        perror("UDP SOCKET ERROR!\n");
        exit(-1);
    }

    // set addr and port struct
    struct sockaddr_in addr;
    socklen_t  addr_len=sizeof(addr);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;       // Use IPV4
    addr.sin_port   = 7878;  
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //htonl(INADDR_ANY)

    
    // 绑定获取数据的端口，作为发送方，不绑定也行
    if (::bind(sockfd_udp, (struct sockaddr*)&addr, addr_len) == -1){
        printf("Failed to bind socket on port");
        close(sockfd_udp);
        exit(1);
    }
    cout<< "111"<<endl;
    Cmd_Msg_T *cmd_info = (Cmd_Msg_T* )malloc(sizeof(Cmd_Msg_T));
    memset(cmd_info, 0, sizeof(Cmd_Msg_T));
    cmd_info->cmd = '4';

    addr.sin_family = AF_INET;
    addr.sin_port   = port_out;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendto(sockfd_udp, cmd_info, sizeof(Cmd_Msg_T), 0, (sockaddr*)&addr, addr_len);
    close(sockfd_udp);
    return 0;
}