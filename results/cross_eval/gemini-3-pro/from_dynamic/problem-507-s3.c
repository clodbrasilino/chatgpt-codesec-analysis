#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *word;
    struct Node *next;
};

void removeTargetWords(struct Node **head, const char *target) {
    if (head == NULL || *head == NULL || target == NULL) {
        return;
    }

    struct Node *current = *head;
    struct Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->word, target) == 0) {
            if (prev == NULL) {
                *head = current->next;
                free(current->word);
                free(current);
                current = *head;
            } else {
                prev->next = current->next;
                free(current->word);
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

void appendNode(struct Node **head, const char *newWord) {
    if (head == NULL || newWord == NULL) {
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return;
    }

    newNode->word = strdup(newWord);
    if (newNode->word == NULL) {
        free(newNode);
        return;
    }
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

int main() {
    struct Node *head = NULL;

    appendNode(&head, "apple");
    appendNode(&head, "banana");
    appendNode(&head, "cherry");
    appendNode(&head, "banana");
    appendNode(&head, "date");

    printList(head);

    removeTargetWords(&head, "banana");

    printList(head);

    freeList(head);

    return 0;
}