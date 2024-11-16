#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

struct node {
    char url[51]; 
    struct node *next;
};


struct node *push(struct node *top, const char *url) {
    struct node *newNode;
    newNode = (struct node *) malloc(sizeof(struct node));
    strcpy(newNode->url, url);
    newNode->next = top;
    top = newNode;
    return top;
}

char *pop(struct node **top) {
    if (*top == NULL) {
        return NULL; 
    }
    struct node *actualNode = *top;
    char *url = malloc(sizeof(actualNode->url));
    strcpy(url, actualNode->url);
    *top = actualNode->next;
    free(actualNode);
    return url;
}

int stackEmpty(struct node *top) {
    return top == NULL ? TRUE : FALSE;
}

void freeStack(struct node *top) {
    struct node *current;
    while (top != NULL) {
        current = top;
        top = top->next;
        free(current);
    }
}

int main() {
    int T;
    scanf("%d", &T); 

    for (int case_num = 1; case_num <= T; case_num++) {
        struct node *backward = NULL;
        struct node *forward = NULL;
        char current_url[51] = "http://www.lightoj.com/";
        char command[10];
        
        printf("Case %d:\n", case_num);

        while (1) {
            scanf("%s", command);
            if (strcmp(command, "QUIT") == 0) {
                break; 
            }
            
            if (strcmp(command, "BACK") == 0) {
                if (stackEmpty(backward)) {
                    printf("Ignored\n");
                } else {
                  
                    forward = push(forward, current_url);
                   
                    strcpy(current_url, pop(&backward));
                    printf("%s\n", current_url);
                }
            } else if (strcmp(command, "FORWARD") == 0) {
                if (stackEmpty(forward)) {
                    printf("Ignored\n");
                } else {
                   
                    backward = push(backward, current_url);
                
                    strcpy(current_url, pop(&forward));
                    printf("%s\n", current_url);
                }
            } else if (strcmp(command, "VISIT") == 0) {
                char url[51];
                scanf("%s", url);
          
                backward = push(backward, current_url);
              
                strcpy(current_url, url);
            
                freeStack(forward);
                forward = NULL;
                printf("%s\n", current_url);
            }
        }
        

        freeStack(backward);
        freeStack(forward);
    }

    return 0;
}
