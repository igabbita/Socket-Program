#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "my_structure.h"

float float_swap_nh(float value){
    
    int temp =  ntohl(*(unsigned int*)&value);
    
    return *(float*)&temp;
    
}

float float_swap_hn(float value){
    
    int temp =  htonl(*(unsigned int*)&value);
    
    return *(float*)&temp;
    
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char wish;
    data_struct client_data,changed_data;
    
    if (argc < 2) {
        fprintf(stderr,"usage: %s port_number1",argv[0]);
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    printf("\nSocket function called on port: %s",argv[1]);
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(portno);
    
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    printf("\nBind function called on port: %s",argv[1]);
    
    listen(sockfd, 10);
    clilen = sizeof(cli_addr);
    
    do{
        printf("\nServer listening on port number %d...\n", portno);
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
        
        if (newsockfd < 0)
            error("ERROR on accept");
        
        if (recv(newsockfd, &client_data, sizeof(client_data), 0) < 0)
	   		error("Read error has occured ");
        else
        {
            client_data.i = ntohl(client_data.i);
            client_data.f = float_swap_nh(client_data.f);
            printf("Values Received from Client_1 are :\n");
            printf("%d\n", client_data.i);
            printf("%f\n", client_data.f);
            printf("%c\n", client_data.c);
        }
        
        if (close(newsockfd) == -1) {
	   		error("Error closing connection with client 1");
        }
        
        printf("Connection with client 1 has been closed\n");
        
        
        //Conversion of the integer, float number and character values
        changed_data.i=2*client_data.i;
        changed_data.f=client_data.f+1;
        
        
        if (client_data.c=='Z')
            changed_data.c='A';
        else if (client_data.c=='z')
            changed_data.c='a';
        else
            changed_data.c= client_data.c+1;
        printf("\nThe updated new values are :\n");
        printf("%d\n", changed_data.i);
        printf("%f\n", changed_data.f);
        printf("%c\n", changed_data.c);
        
        //connecting socket for client2
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        
        // Prepare data before sending over the wire.
        changed_data.i = htonl(changed_data.i);
        changed_data.f = float_swap_hn(changed_data.f);
        
        if (send(newsockfd, &changed_data, sizeof(changed_data), 0) < 0)
        {
            error("Read error has occured ");
        }
        
        if (close(newsockfd) == -1)
            error("Error closing connection with client 2");
        
        printf("\nSent changed data to client2 - closing connection!\n");
        printf("Do you wish to continue:y/n?\n");
        
        scanf( "%c", &wish); 
    }while(wish=='y');
    
    
    printf("Server Quitting!\n");
    return 0; 
}

