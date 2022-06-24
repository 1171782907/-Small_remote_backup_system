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
    int sk ; // socket descriptor
    int port_out = 30434;
    sockaddr_in remote ; // socket address for remote side
    char buf[3000] ; // buffer for response from remote
    int mesglen ; // actual length of the message
    // create the socket
    sk = socket(AF_INET,SOCK_STREAM,0) ;
    // designate the addressing family
    remote.sin_family = AF_INET ;
    // get the address of the remote host and store
    remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    // get the port used on the remote side and store
    remote.sin_port = port_out;
    // connect to other side
    if(connect(sk, (struct sockaddr *)&remote, sizeof(remote)) < 0) {
        cout << "connection error!\n" ;
        close(sk);
        exit(1);
    }
    // send the message to the other side
    string s = "Have you heard about the new corduroy pillows?\nThey are making headlines!";
    write(sk,s.c_str(),s.size());
    // wait for a response and print it
    // mesglen = read(sk,buf,3000) ;
    // buf[mesglen] = '\0';
    // cout << buf << endl;
    // // send message telling it to shut down

    // write(sk,MSG2,strlen(MSG2));
    // // close the socket and exit
    close(sk);
    return 0;
}