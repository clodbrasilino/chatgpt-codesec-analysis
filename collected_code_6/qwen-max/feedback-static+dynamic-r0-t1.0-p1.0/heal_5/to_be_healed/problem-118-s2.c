#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    char *item;
    struct List *next;
} List;

List* createNode(const char *str) {
    List *newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL) return NULL;
    newNode->item = strdup(str);
    if (newNode->item == NULL) {
        free(newNode);
        return NULL;
    }
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got ["python","p"
  */

List* stringToList(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    List *head = NULL;
    const char *tokenStart = str;
    while (*str) {
        if (*str == ' ') {
            if (tokenStart != str) {
                List *newNode = createNode(strndup(tokenStart, str - tokenStart));
                if (newNode == NULL) return NULL;
                if (head == NULL) {
                    head = newNode;
                } else {
                    List *p = head;
                    while (p->next) {
                        p = p->next;
                    }
                    p->next = newNode;
                }
            }
            tokenStart = str + 1;
        }
        str++;
    }

    if (tokenStart != str) {
        List *newNode = createNode(strndup(tokenStart, str - tokenStart));
        if (newNode == NULL) return NULL;
        if (head == NULL) {
            head = newNode;
        } else {
            List *p = head;
            while (p->next) {
                p = p->next;
            }
            p->next = newNode;
        }
    }

    return head;
}

int main() {
    const char input[] = "python programming";
    List *list = stringToList(input);

    for (List *p = list; p != NULL; p = p->next) {
        printf("%s\n", p->item);
    }

    freeList(list);
    return 0;
}