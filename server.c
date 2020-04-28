#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT 8080 
   
int main() { 
    int sockfd; 
    char buffer[BUFSIZ]; 
    char *msg[50]; 
    struct sockaddr_in servaddr, cliaddr; 
    
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
     
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
    
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
    
    len = sizeof(cliaddr);  //len is value/resuslt 
    while(1){
        n = recvfrom(sockfd, (char *)buffer, BUFSIZ, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer);
        fgets(msg,50,stdin); 
        sendto(sockfd, (const char *)msg, strlen(msg),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);  
    }  
    return 0; 
} 