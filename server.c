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
    char buffer[1055736]; 
    FILE *fp; 
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
    
    len = sizeof(cliaddr);
    while(1){
        while(1){
        n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        if (n<0) {
            perror("Error in receiving file");
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer);
        fp = fopen("recv.txt","w+");
        if(fwrite(buffer,1,sizeof(buffer),fp)<0){
            perror("Error writing file");
            exit(EXIT_FAILURE);
        }
        printf("File written successfully");
        break;
        }
       break;
    }  
    return 0; 
} 
