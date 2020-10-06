#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096	
#define SERV_PORT 3000


int main(int argc, char const *argv[])
{
	int sockfd, connfd, n;
	struct sockaddr_in servaddr;
	int val_read;
	char sendline[MAXLINE], recvline[MAXLINE];
	int status = 1;
	char buffer[1024];

	// Create a socker for the cliet
	// if sockfd < 0 there was an error in the creation of the socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Problem in creating the socket");
		exit(2);
	}


	// Create the socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(SERV_PORT);		

	// Connection of the client to the socket
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("Problem in connecting to the server");
		exit(3);
	}

	do{
		// val_read = recv(sockfd, buffer, 1024, 0);
		// printf("%s\n", buffer);
		printf("Enter week_day: \n");
   		fgets(buffer, MAXLINE, stdin); 
		send(sockfd, buffer, MAXLINE, 0);

		 while ( (n = recv(sockfd, buffer, MAXLINE,0)) > 0)  {
   			printf("%s","String received from server:\n");
   			if (strlen(buffer) > 0)
   			{
   				puts(buffer);
   			}
  		}

  		if (n < 0) {
  			perror("Read error"); 
  			exit(1);
 		}
	}while(strcmp(buffer, "bye") == 0);


	exit(0);
}