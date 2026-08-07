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
 
while (fgets(line, MAXLINE, stdin) != NULL) { 
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

printf("\nPrint of list\n");
printf("---------------\n");

for (current = head; current != NULL; current = current->next) {
    printf("%s", current->text);
}

return 0;

}