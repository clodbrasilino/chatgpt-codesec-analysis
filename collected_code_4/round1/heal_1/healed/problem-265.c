#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int next;
} Node;

typedef struct List {
    Node* nodes;
    size_t length;
} List;

List* split_list(List* list, int n) {
    if (list == NULL || n <= 0 || n > list->length) {
        return NULL;
    }

    size_t new_list_count = (list->length + n - 1) / n;
    List* new_lists = malloc(sizeof(List) * new_list_count);
    if (new_lists == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < new_list_count; i++) {
        new_lists[i].length = (list->length - i * n > n) ? n : list->length - i * n;
        new_lists[i].nodes = list->nodes + i * n;
    }

    return new_lists;
}

int main() {
    List list;
    Node nodes[10];
    for (int i = 0; i < 10; i++) {
        nodes[i].data = i;
        nodes[i].next = i + 1;
    }
    nodes[9].next = -1;

    list.nodes = nodes;
    list.length = 10;

    List* new_lists = split_list(&list, 3);
    if (new_lists != NULL) {
        for (size_t i = 0; i < (list.length + 3 - 1) / 3; i++) {
            printf("List %zu:\n", i);
            for (size_t j = 0; j < new_lists[i].length; j++) {
                printf("Node %zu: %d\n", j, new_lists[i].nodes[j].data);
            }
        }

        free(new_lists);
    }
    else {
        printf("Failed to split list\n");
    }

    return 0;
}