#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct {
    List *list;
    int count;
} ListCount;

int list_compare(List *a, List *b) {
    Node *current_a = a->head, *current_b = b->head;
    while (current_a && current_b) {
        if (current_a->value != current_b->value) return 0;
        current_a = current_a->next;
        current_b = current_b->next;
    }
    return !current_a && !current_b;
}

List* create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void add_value(List *list, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

ListCount* count_frequency(List *lists[], int n) {
    ListCount *result = NULL;
    int i, j, found;
    for (i = 0; i < n; ++i) {
        found = 0;
        for (j = 0; j < i; ++j) {
            if (list_compare(lists[i], lists[j])) {
                result[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            ListCount new_entry = { .list = lists[i], .count = 1 };
            size_t new_size = (i + 1) * sizeof(*result);
            result = (ListCount*)realloc(result, new_size);
            if (result) {
                result[i] = new_entry;
            }
        }
    }
    return result;
}

void print_result(ListCount *result, int n) {
    for (int i = 0; i < n; ++i) {
        printf("List: ");
        for (Node *node = result[i].list->head; node; node = node->next) {
            printf("%d ", node->value);
        }
        printf(" -> Count: %d\n", result[i].count);
    }
}

void free_lists(List *lists[], int n) {
    for (int i = 0; i < n; ++i) {
        Node *current, *next;
        for (current = lists[i]->head; current; current = next) {
            next = current->next;
            free(current);
        }
        free(lists[i]);
    }
}

int main() {
    List *lists[5];
    for (int i = 0; i < 5; ++i) {
        lists[i] = create_list();
        for (int v : (int[]){1, 2, 3, 4, 5}) {
            add_value(lists[i], v + i);  // Modify values to simulate different lists
        }
    }
    
    ListCount *result = count_frequency(lists, 5);
    
    print_result(result, 5);

    free_lists(lists, 5);
    free(result);

    return 0;
}