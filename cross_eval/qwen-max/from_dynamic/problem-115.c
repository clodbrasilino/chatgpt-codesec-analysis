#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int count;  // Assume this is the number of key-value pairs
} Dictionary;

struct Node {
    Dictionary* dict;
    struct Node* next;
};

typedef struct {
    struct Node* head;
} List;

bool areAllDictionariesEmpty(List* list) {
    if (!list) {
        return false;
    }
    for (struct Node* current = list->head; current != NULL; current = current->next) {
        if (current->dict->count != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary d1 = {0};
    Dictionary d2 = {0};
    Dictionary d3 = {0};

    List list = {0};
    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));

    node1->dict = &d1;
    node1->next = node2;

    node2->dict = &d2;
    node2->next = node3;

    node3->dict = &d3;
    node3->next = NULL;

    list.head = node1;

    bool result = areAllDictionariesEmpty(&list);

    free(node1);
    free(node2);
    free(node3);

    return 0;
}