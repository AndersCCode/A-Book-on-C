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
struct lnode *prev = NULL;

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

/* Print before delete */
printf("\nThe list\n");
printf("---------\n");

for (current = head; current != NULL; current = current->next) {
    printf("%s", current->text);
}

/* Delete object */
for (current = head; current != NULL; current = current->next) {
    
    prev = current->prev;

    if (strstr(current->text, "book") != NULL) { // Choose character or word to delete 
        if (current->prev == NULL) { // object at the beginning of the list
            head = current->next;
            free(current);
        }
        else if (current->prev != NULL && current->next != NULL) { // object in the middle of the list
            prev->next = current->next;
            free(current);
        }
        else if (current->next == NULL) { // object is last in the list
            prev->next = NULL;
            tail = prev;
            free(current);
        }
    }    
}

/* Print after delete */
printf("\n\nThe list after delete\n");
printf("----------------------\n");

for (current = head; current != NULL; current = current->next) {
    printf("%s", current->text);
}

return 0;
}