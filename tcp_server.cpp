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
    int sk, sk2 ; // socket descriptors
    sockaddr_in remote ; // socket address for remote
    sockaddr_in local ; // socket address for us
    char buf[DATA_BUF_LEN] ; // buffer from remote
    char retbuf[DATA_BUF_LEN] ; // buffer to remote
    socklen_t rlen = sizeof(remote) ; // length of remote address
    socklen_t len = sizeof(local) ; // length of local address
    int moredata = 1 ; // keep processing or quit
    int mesglen ; // actual length of message
    // create the socket
    sk = socket(AF_INET,SOCK_STREAM,0);
    if(sk < 0) {
        perror("tcp SOCKET ERROR!\n");
        exit(-1);
    }
    memset(&local, 0, len);
    // set up the socket
    local.sin_family = AF_INET ; // internet family
    local.sin_port = 0; 
    local.sin_addr.s_addr = htonl(INADDR_ANY) ; // wild card machine address
    // let system choose the port
    // bind the name (address) to a port
    ::bind(sk,(struct sockaddr *)&local,sizeof(local)) ;
    // get the port name and print it out
    getsockname(sk,(struct sockaddr *)&local,&len) ;
    cout<<local.sin_port<<endl;
    // tell OS to queue (up to 1) connection requests
    listen(sk, 1);
    // wait for connection request, then close old socket
    sk2 = accept(sk, (struct sockaddr *)0, (socklen_t *)0) ;
    close(sk);
    if(sk2 == -1)cout << "accept failed!\n" ;
    else { 
        mesglen = read(sk2,buf,DATA_BUF_LEN);
        buf[mesglen] = '\0' ;
        cout << buf << endl;;
    }
    close(sk2);
    exit(0);
    return 0;
}