#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 8080 

// Driver code 
int main() { 
	int sockfd;
	size_t file_size;
	char *msg; 
	FILE *fp;
	char file_name[] = "send.txt";
	struct sockaddr_in servaddr; 

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd<0) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        perror("Connect failed"); 
        exit(EXIT_FAILURE); 
    } 
	
	int n, len;
	fp = fopen(file_name,"r");
	if (fp == NULL){
		perror("File does not exist");
		exit(EXIT_FAILURE);
	}
	printf("File opened successfully\n");
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	msg = (char*)calloc(file_size, sizeof(char));
	printf("%ld\n",sizeof(msg));
	if(fread(msg, file_size, 1, fp)<=0){
		perror("Error in copy the file to buffer");
		exit(EXIT_FAILURE);
	}
	printf("File copied into the msg successfully \n");
	printf("%ld\n",sizeof(msg));
	printf("%s\n",msg);
	sendto(sockfd, (const char *)msg, strlen(msg),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	fclose(fp);
	close(sockfd); 
	return 0; 
} 
