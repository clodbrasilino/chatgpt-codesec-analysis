#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    char *item;
    struct List *next;
} List;

List* createNode(char *str) {
    List *newNode = (List*)malloc(sizeof(List));
    newNode->item = strdup(str);
    newNode->next = NULL;
    return newNode;
}

void freeList(List *head) {
    while (head != NULL) {
        List *temp = head;
        head = head->next;
        free(temp->item);
        free(temp);
    }
}

List* stringToList(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    List *head = NULL;
    List *tail = NULL;

    const char *tokenStart = str;
    while (*str) {
        if (*str == ' ') {
            if (tokenStart != str) {
                List *newNode = createNode(strndup(tokenStart, str - tokenStart));
                if (head == NULL) {
                    head = tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
            tokenStart = str + 1;
        }
        str++;
    }

    if (tokenStart != str) {
        List *newNode = createNode(strndup(tokenStart, str - tokenStart));
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

int main() {
    char input[] = "This is a test string";
    List *list = stringToList(input);

    for (List *p = list; p != NULL; p = p->next) {
        printf("%s\n", p->item);
    }

    freeList(list);
    return 0;
}