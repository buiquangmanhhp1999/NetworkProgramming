#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "LinkedList.h"



void push_first(node_t *head, char code[], char sub[], char am_pm[], int week_day, char period[], char week[], char room[]) {
    node_t *new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    strcpy(new_node->next->code_sub, code);
    strcpy(new_node->next->subject, sub);
    new_node->next->week_day = week_day;
    strcpy(new_node->next->AM_PM, am_pm);
    strcpy(new_node->next->week, week);
    strcpy(new_node->next->period, period);
    strcpy(new_node->next->room, room);
    new_node->next = head;
    head = new_node;
}

void push(node_t *head, char code[], char sub[], char am_pm[], int week_day, char period[], char week[], char room[]) {
    node_t *current = head;

    if (head == NULL)
    {
        push_first(head, code, sub, am_pm, week_day, period, week, room);
    }

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (node_t *) malloc(sizeof(node_t));
    strcpy(current->next->code_sub, code);
    strcpy(current->next->subject, sub);
    current->next->week_day = week_day;
    strcpy(current->next->AM_PM, am_pm);
    strcpy(current->next->week, week);
    strcpy(current->next->period, period);
    strcpy(current->next->room, room);
    current->next->next = NULL;
}

void printList(node_t *head)
{
    node_t *current = head;
    char week[20];

    printf("%10s|%20s|%10s|%10s|%10s|%15s|%10s\n", "Code", "Course", "Week Day", "AM/PM", "Period", "Week", "Room");
    printf("==================================================================================================\n");
    while(current != NULL)
    {   if(current->week_day == 2)
        {
            strcpy(week, "Monday");
        }
        else if (current->week_day == 3)
        {
            strcpy(week, "Tuesday");
        }
        else if (current->week_day == 4)
        {
            strcpy(week, "Wednesday");
        }
        else if (current->week_day == 5)
        {
            strcpy(week, "Thursday");
        }
        else if (current->week_day == 6)
        {
            strcpy(week, "Friday");
        }
        else if (current->week_day == 7)
        {
            strcpy(week, "Saturday");
        }

        printf("%10s|%20s|%10s|%10s|%10s|%15s|%10s\n", current->code_sub, current->subject, week, current->AM_PM, current->period, current->week, current->room);
        current = current->next;
    }
}


node_t *searchDay(node_t *head, int week_day)
{
    node_t *current = head;
    char week[20];

    printf("%10s|%20s|%10s|%10s|%10s|%15s|%10s\n", "Code", "Course", "Week Day", "AM/PM", "Period", "Week", "Room");
    printf("==================================================================================================\n");

    while(current != NULL)
    {   
        if (current->week_day == week_day)
        {
            if(current->week_day == 2)
            {
                strcpy(week, "Monday");
            }
            else if (current->week_day == 3)
            {
                strcpy(week, "Tuesday");
            }
            else if (current->week_day == 4)
            {
                strcpy(week, "Wednesday");
            }
            else if (current->week_day == 5)
            {
                strcpy(week, "Thursday");
            }
            else if (current->week_day == 6)
            {
            strcpy(week, "Friday");
            }
            else if (current->week_day == 7)
            {
                strcpy(week, "Saturday");
            }
            return current;
        }
        current = current->next;
    }

    return NULL;
}