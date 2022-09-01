#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "sys/un.h"
#include "sys/socket.h"

int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  char input;
  int n=1;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
 while(1)
 {
    printf("Please type in Message sending to Server: ");
    fgets(buffer,sizeof(buffer),stdin);
    /*printf("Please type in Message sending to Server:");*/
    send(sock, buffer, sizeof(buffer),0);
    
    bzero(buffer,1024);
    recv(sock,buffer,sizeof(buffer),0);
    printf("Message Reveived from server: %s\n",buffer);
        
    }
    close(sock);
    printf("Disconnected from the server.\n");

  return 0;
  
}
