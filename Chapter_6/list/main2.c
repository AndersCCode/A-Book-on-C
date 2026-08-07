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

while (fgets(line, sizeof(line), file) != NULL) { 
    char *save = (char *) malloc(strlen(line) + 1);
    strcpy(save, line);
    printf("[Debug] line: %s\n", line);

    struct lnode *new = (struct lnode *) malloc(sizeof(struct lnode));

    new->text = save;
    new->next = NULL;
    tail = new;
    printf("[Debug] new->text: %s new->next: %p\n", new->text, new->next);
    
    if (head == NULL) {
        head = new;
        printf("[Debug] head.text: %s", head->text);
    }

    if (tail != NULL) {
        tail->next = new;
        printf("[Debug] tail.text: %s", tail->text);
    }
    
    tail = new;
}

printf("[Debug] After while\n");

for (current = tail; current != NULL; current = current->prev) {
    printf("%s", current->text);
}

return 0;

}