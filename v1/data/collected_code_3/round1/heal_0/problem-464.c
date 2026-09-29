#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int value;
    struct Node* next;
};

struct Node* newNode(int key, int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

int checkValues(struct Node* node) {
    if (node == NULL) {
        return 1;
    }

    int value = node->value;
    node = node->next;

    while (node != NULL) {
        if (node->value != value) {
            return 0;
        }
        node = node->next;
    }

    return 1;
}

int main() {
    struct Node* node = newNode(1, 10);
    node->next = newNode(2, 10);
    node->next->next = newNode(3, 10);

    if (checkValues(node)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not the same.\n");
    }

    return 0;
}