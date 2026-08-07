#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(void) {
    
struct lnode {
    char *text;
    struct lnode *prev;
    struct lnode *next;
};

struct lnode *head = NULL;
struct lnode *tail = NULL;
struct lnode *current;

char line[MAXLINE];

FILE *file = fopen("text.txt", "r");
if (!file) {
    printf("Could not open file \n");
    return 1;
} 

while (fgets(line, sizeof(line), file)) { 
    char *save = (char *) malloc(strlen(line) + 1);
    strcpy(save, line);

    struct lnode *new = (struct lnode *) malloc(sizeof(struct lnode));

    new->text = save;
    new->next = NULL;
    new->prev = tail;

    if (head == NULL) head = new;
    
    if (tail != NULL) tail->next = new;
   
    tail = new;
}

for (current = head; current != NULL; current = current->next) {
    printf("%s", current->text);
}

return 0;
}