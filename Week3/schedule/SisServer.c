#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "LinkedList.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

void read_file(FILE *file, node_t *test_list)
{
	char line[MAX_LINE_LENGTH];
    int line_count = 0;
    char delim[] = "\t";


    /* Get each line until there are none left */
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        /* Print each line */
        // printf("line[%06d]: %s", ++line_count, line);
        int index = 0;
        char *ptr = strtok(line, delim);
    	char code[10] = "";
    	char sub[40] = "";
    	char am_pm[10] = "";
    	char period[10] = "";
    	char week[20] = "";
    	char room[20] = "";
    	int week_day;

        // split each line by tab symbol
		while(ptr != NULL)
		{
			if(index == 0)
			{
				strcpy(code, ptr);
			}
			else if (index == 1)
			{
				strcpy(sub, ptr);
			}
			else if (index == 2)
			{
				char colon_sym[] = ",";
				char *ptr_1 = strtok(ptr, colon_sym);
				int index1 = 0;

				while(ptr_1 != NULL)
				{
					if(index1 == 0)
					{
						week_day = ptr_1[0]%49;

						if (ptr_1[1]%49 == 0)
						{
							strcpy(am_pm, "Morning");
						}
						else
						{
							strcpy(am_pm, "Afternoon");
						}

						period[0] = ptr_1[2];
					}
					else if (index1 == 1)
					{
						period[1] = '-';
						period[2] = ptr_1[2];
						period[3] = '\0';
					}
					else if (index1 >=2 && index1 <= 4)
					{
						strcat(week, ptr_1);

						if (index1 != 4)
							strcat(week, ",");
					}
					else if (index1 == 5)
					{
						strcpy(room, ptr_1);
						int length = strlen(room);
						// room[length-1] = '\0';
					}

					index1++;
					ptr_1 = strtok(NULL, colon_sym);
				}
			}
			index++;
			ptr = strtok(NULL, delim);
		}
		push(test_list, code, sub, am_pm, week_day, period, week, room);
        /* Add a trailing newline to lines that don't already have one */
        if (line[strlen(line) - 1] != '\n')
            printf("\n");
  //       printf("Code: %s\n", code);
  //       printf("Sub : %s\n", sub);
  //       printf("week_day: %d\n", week_day);
  //       printf("period: %s\n", period);
		// printf("am_pm: %s\n", am_pm);
		// printf("week: %s\n", week);
		// printf("room: %s\n", room);

    }
}


int main()
{
	FILE *file;
 	int listenfd, connfd, n;
 	pid_t childpid;
 	socklen_t client;
 	char buf[MAXLINE];
 	struct sockaddr_in cliaddr, servaddr;

 	//creation of the socket
 	listenfd = socket (AF_INET, SOCK_STREAM, 0);
	
	 //preparation of the socket address 
 	servaddr.sin_family = AF_INET;
 	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	servaddr.sin_port = htons(SERV_PORT);
	
 	bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
 	listen (listenfd, LISTENQ);
	
 	printf("%s\n","Server running...waiting for connections.");


	if ((file = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");

        // Program exits if file pointer returns NULLh
        exit(1);
    }


    node_t * test_list = (node_t *) malloc(sizeof(node_t));

    // read data from database
    read_file(file, test_list);
    char answer[MAXLINE]="";
    node_t *reply;
    char week[20];


    for ( ; ; ) {
  	 	client = sizeof(cliaddr);
  		connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &client);
  		printf("%s\n","Received request...");
				
  		while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
   			printf("%s","String received from and resent to the client:");
   			if (strlen(buf) > 0)
   			{
   				printf(" %s\n", buf);
   			}

   			int week_day = buf[0]%49;
   			reply = searchDay(test_list, week_day);

            if(reply->week_day == 2)
            {
                strcpy(week, "Monday");
            }
            else if (reply->week_day == 3)
            {
                strcpy(week, "Tuesday");
            }
            else if (reply->week_day == 4)
            {
                strcpy(week, "Wednesday");
            }
            else if (reply->week_day == 5)
            {
                strcpy(week, "Thursday");
            }
            else if (reply->week_day == 6)
            {
            	strcpy(week, "Friday");
            }
            else if (reply->week_day == 7)
            {
                strcpy(week, "Saturday");
            }
   			strcat(answer, reply->code_sub);
   			strcat(answer, ", ");
   			strcat(answer, reply->subject);
   			strcat(answer, ", ");
   			strcat(answer, week);
   			strcat(answer, ", ");
   			strcat(answer, reply->AM_PM);
   			strcat(answer, ", ");
   			strcat(answer, reply->period);
   			strcat(answer, ", ");
   			strcat(answer, reply->week);
   			strcat(answer, ", ");
   			strcat(answer, reply->room);
   			send(connfd, answer, MAXLINE, 0);
  		}

  		if (n < 0) {
  			perror("Read error"); 
  			exit(1);
 		}
 		close(connfd);
  	}
}