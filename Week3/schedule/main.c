#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "LinkedList.h"




int main() {
    char line[MAX_LINE_LENGTH];
    FILE *file;
    int line_count = 0;
    char delim[] = "\t";

    node_t * test_list = (node_t *) malloc(sizeof(node_t));

    if ((file = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULLh
        exit(1);
    }


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
    
    fclose(file);

    printList(test_list);
    return 0;
}
