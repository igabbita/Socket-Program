#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "my_structure.h"

float float_swap(float value){
    
    int temp =  ntohl(*(unsigned int*)&value);
    
    return *(float*)&temp;
    
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    data_struct changed_data;
    
    if (argc < 3) {
        fprintf(stderr,"usage: %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]); //Convert ASCII to interger
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket file descriptor
    
    if (sockfd < 0)
        error("ERROR opening socket");\
    
    server = gethostbyname(argv[1]);
    
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    
    
    bzero((char *) &serv_addr, sizeof(serv_addr)); //clear the memory for server address
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    
    serv_addr.sin_port = htons(portno);
    
    printf("Client 2 attemping connection with server host %s on port %d\n", argv[1], portno);
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    
    printf("Connection established!!");
    
    if (recv(sockfd, &changed_data, sizeof(changed_data), 0) < 0)
    {
        error("Write error has occured ");
    }
    
    printf("The values received from the Server are :\n");
    printf("%d\n", ntohl(changed_data.i));
    printf("%f\n", float_swap(changed_data.f));
    printf("%c\n", changed_data.c);
    printf("Client 2 exiting!!\n");
    return 0;
}

