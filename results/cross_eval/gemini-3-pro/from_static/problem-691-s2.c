#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    int key;
    Node* values;
} Group;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_to_group(Group** groups, int* group_count, int key, int value) {
    for (int i = 0; i < *group_count; i++) {
        if ((*groups)[i].key == key) {
            Node* current = (*groups)[i].values;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = create_node(value);
            return;
        }
    }

    Group* temp = realloc(*groups, (*group_count + 1) * sizeof(Group));
    if (!temp) {
        exit(EXIT_FAILURE);
    }
    *groups = temp;

    (*groups)[*group_count].key = key;
    (*groups)[*group_count].values = create_node(value);
    (*group_count)++;
}

void print_and_free_groups(Group* groups, int group_count) {
    for (int i = 0; i < group_count; i++) {
        printf("Key: %d, Values: [", groups[i].key);
        Node* current = groups[i].values;
        while (current != NULL) {
            printf("%d", current->value);
            if (current->next != NULL) {
                printf(", ");
            }
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        printf("]\n");
    }
    free(groups);
}

void group_tuples(Tuple* tuples, int num_tuples) {
    Group* groups = NULL;
    int group_count = 0;

    for (int i = 0; i < num_tuples; i++) {
        add_to_group(&groups, &group_count, tuples[i].second, tuples[i].first);
    }

    print_and_free_groups(groups, group_count);
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 20},
        {5, 30}
    };
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    group_tuples(tuples, num_tuples);

    return EXIT_SUCCESS;
}