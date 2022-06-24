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
#define BUFLEN 356


int main(){
    int sockfd_udp;
    sockaddr_in remote ; // socket address for remote
    sockaddr_in local ; // socket address for us
    char buf[BUFLEN] ; // buffer from remote
    char retbuf[BUFLEN] ; // buffer to remote
    socklen_t rlen = sizeof(remote) ; // length of remote address
    socklen_t len = sizeof(local) ; // length of local address
    int moredata = 1 ; // keep processing or quit
    int mesglen ; // actual length of message
    //create udp socekt
    sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_udp < 0) {
        perror("UDP SOCKET ERROR!\n");
        exit(-1);
    }

    // init data is zero
    memset(&local, 0, len);
    // TCP/IP – IPv4
    local.sin_family = AF_INET;
    // bind port
    local.sin_port = 0; //let system choose the port    
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind the name (address) to a port
    if(::bind(sockfd_udp, (struct sockaddr*)& local, sizeof(local)) == -1){
        perror("bind ERROR!\n");
        exit(1);
    }

    // get the port name and print it out
    getsockname(sockfd_udp,(struct sockaddr *)&local,&len) ;
    cout << "Waiting UDP command @: " << local.sin_port << "\n";
    while(1){
        mesglen = recvfrom(sockfd_udp,buf,1000,0,(struct sockaddr *)&remote, &rlen);
        buf[mesglen] = '\0';
        Cmd_Msg_T *cmd_info = (Cmd_Msg_T* )buf; 
        cout<<"shoudao"<<endl;
        cout << cmd_info->cmd << endl ;
        cout << cmd_info->filename << endl ;
        cout << cmd_info->port << endl ;
        cout << cmd_info->size << endl ;
        cout << cmd_info->error << endl ;
        cout << remote.sin_port << endl ;
        cout << remote.sin_addr.s_addr << endl ;



    }
    

    // while( moredata ) {
    //     // wait for a message and print it
       
    //     // moredata = rot13(buf,retbuf) ;
    //     if( moredata ) {
    //         // send a reply, using the address given in remote
    //         sendto(sockfd_udp,retbuf,strlen(retbuf),0,(struct sockaddr *)&remote, sizeof(remote));
    //     }
    // }
    close(sockfd_udp);
    return 0;
}