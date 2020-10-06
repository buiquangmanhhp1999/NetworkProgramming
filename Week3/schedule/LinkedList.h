#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

static int MAX_LINE_LENGTH = 100;

typedef struct node {
    char code_sub[10];
    char subject[40];
    int week_day;
    char AM_PM[10];
    char period[10];
    char week[20];
    char room[20];
    struct node *next;
} node_t;


void push_first(node_t *head, char code[], char sub[], char am_pm[], int week_day, char period[], char week[], char room[]);
void push(node_t *head, char code[], char sub[], char am_pm[], int week_day, char period[], char week[], char room[]);
void printList(node_t *head);
node_t *searchDay(node_t *head, int week_day);