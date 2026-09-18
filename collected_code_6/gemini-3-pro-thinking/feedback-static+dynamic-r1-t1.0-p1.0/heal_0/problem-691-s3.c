#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int first;
    int second;
};

struct Group {
    int key;
    int *values;
    size_t count;
    size_t capacity;
    struct Group *next;
};

struct Group* create_group(int key) {
    struct Group *new_group = (struct Group *)malloc(sizeof(struct Group));
    if (!new_group) {
        return NULL;
    }
    
    new_group->key = key;
    new_group->count = 0;
    new_group->capacity = 4;
    
    new_group->values = (int *)malloc(new_group->capacity * sizeof(int));
    if (!new_group->values) {
        free(new_group);
        return NULL;
    }
    
    new_group->next = NULL;
    return new_group;
}

void free_groups(struct Group *head) {
    struct Group *current = head;
    while (current != NULL) {
        struct Group *next = current->next;
        free(current->values);
        free(current);
        current = next;
    }
}

struct Group* group_tuples(const struct Tuple *tuples, size_t num_tuples) {
    if (!tuples || num_tuples == 0) {
        return NULL;
    }

    struct Group *head = NULL;

    for (size_t i = 0; i < num_tuples; ++i) {
        int value = tuples[i].first;
        int key = tuples[i].second;

        struct Group *current = head;
        struct Group *prev = NULL;
        
        while (current != NULL && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            current = create_group(key);
            if (!current) {
                free_groups(head);
                return NULL;
            }
            if (prev == NULL) {
                head = current;
            } else {
                prev->next = current;
            }
        }

        if (current->count >= current->capacity) {
            size_t new_capacity = current->capacity * 2;
            int *new_values = (int *)realloc(current->values, new_capacity * sizeof(int));
            if (!new_values) {
                free_groups(head);
                return NULL;
            }
            current->values = new_values;
            current->capacity = new_capacity;
        }

        current->values[current->count++] = value;
    }

    return head;
}

int main(void) {
    struct Tuple tuples[] = {
        {1, 10}, 
        {2, 20}, 
        {3, 10}, 
        {4, 30}, 
        {5, 20}, 
        {6, 10}
    };
    
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    struct Group *grouped = group_tuples(tuples, num_tuples);
    if (!grouped) {
        return EXIT_FAILURE;
    }

    struct Group *current = grouped;
    while (current != NULL) {
        printf("Key %d: [", current->key);
        for (size_t i = 0; i < current->count; ++i) {
            printf("%d%s", current->values[i], (i < current->count - 1) ? ", " : "");
        }
        printf("]\n");
        current = current->next;
    }

    free_groups(grouped);
    return EXIT_SUCCESS;
}