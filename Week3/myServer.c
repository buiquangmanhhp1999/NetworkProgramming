#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>


#define MAXLINE 4096	
#define SERV_PORT 3000

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char client_ip_result[100];
	char client_port_result[30];
	char buffer[1024];
	char *hello = "Hello from server";
	int status = 1;

	// create socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(1);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(2); 
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(SERV_PORT); 

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(3); 
    }

    //listen, chi dinh socket lang nghe ket noi
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(4); 
    } 

    //accept, chap nhan ket noi
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
    { 
       perror("accept failed");
       exit(5);
    } 
    printf("DUMP\n");
    // ip address of client
    char str_cli_ip[INET_ADDRSTRLEN];
	struct sockaddr_in* ip_client = (struct sockaddr_in*)&address;

	inet_ntop(AF_INET, &ip_client->sin_addr, str_cli_ip, INET_ADDRSTRLEN);
	// port of client
	char bye[10];
	char strport[10];
	int port = ntohs(ip_client->sin_port);

	strcpy(client_ip_result, "The IP Address of Client: ");
	strcat(client_ip_result, str_cli_ip);
	strcat(client_ip_result, "\n");
	send(new_socket, client_ip_result, strlen(client_ip_result), 0);

	strcpy(client_port_result, "The number port of client: ");
	sprintf(strport, "%d", port);
	strcat(client_port_result, strport);
	strcat(client_port_result, "\n");
	send(new_socket, client_port_result, strlen(client_port_result), 0);

	strcpy(bye, "bye\n");
	send(new_socket, bye, strlen(bye), 0);
	close(new_socket);
	return 0;
}
