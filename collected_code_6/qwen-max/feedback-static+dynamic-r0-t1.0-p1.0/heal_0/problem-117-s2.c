#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

void addNode(LinkedList *list, char *value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = strdup(value);
    newNode->next = list->head;
    list->head = newNode;
}

int isConvertibleToFloat(char *str) {
    if (str == NULL || *str == '\0') return 0;

    int hasDecimalPoint = 0;
    while (*str) {
        if (isdigit(*str)) {
            str++;
        } else if (*str == '.' && !hasDecimalPoint) {
            hasDecimalPoint = 1;
            str++;
        } else if (*str == '-' || *str == '+') {
            if (str != value) break; // Only one leading sign allowed
        } else {
            return 0;
        }
    }

    return 1;
}

void convertToFloat(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        if (isConvertibleToFloat(current->value)) {
            float f = strtof(current->value, NULL);
            char *newValue = (char *)malloc(50 * sizeof(char));
            snprintf(newValue, 50, "%f", f);
            free(current->value);
            current->value = newValue;
        }
        current = current->next;
    }
}

void printList(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        printf("%s -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        free(temp->value);
        current = current->next;
        free(temp);
    }
}

int main() {
    LinkedList list = { .head = NULL };
    addNode(&list, "42");
    addNode(&list, "3.14");
    addNode(&list, "hello");
    addNode(&list, "-7.2e-3");

    printf("Original List: ");
    printList(&list);

    convertToFloat(&list);

    printf("Converted List: ");
    printList(&list);

    freeList(&list);
    return 0;
}