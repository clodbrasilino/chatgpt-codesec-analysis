#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    int count;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} HashTable;

static unsigned int hash(int key, int size) {
    return (unsigned int)(key % size + size) % size;
}

static Node *find_node(HashTable *ht, int key, int size) {
    unsigned int index = hash(key, size);
    Node *current = ht[index].head;
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static HashTable *create_hash_table(int size) {
    HashTable *ht = (HashTable *)calloc(size, sizeof(HashTable));
    if (ht == NULL) {
        return NULL;
    }
    return ht;
}

static void insert_or_increment(HashTable *ht, int key, int size) {
    unsigned int index = hash(key, size);
    Node *current = ht[index].head;
    while (current != NULL) {
        if (current->key == key) {
            current->count++;
            return;
        }
        current = current->next;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    new_node->key = key;
    new_node->count = 1;
    new_node->next = ht[index].head;
    ht[index].head = new_node;
}

static void free_hash_table(HashTable *ht, int size) {
    for (int i = 0; i < size; i++) {
        Node *current = ht[i].head;
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}

int **frequency_of_elements(int **list_of_lists, const int *list_sizes, int num_lists, int *total_elements, int **freq_values, int **freq_counts) {
    if (list_of_lists == NULL || list_sizes == NULL || num_lists <= 0) {
        *total_elements = 0;
        *freq_values = NULL;
        *freq_counts = NULL;
        return NULL;
    }

    int total = 0;
    for (int i = 0; i < num_lists; i++) {
        if (list_sizes[i] < 0) {
            *total_elements = 0;
            *freq_values = NULL;
            *freq_counts = NULL;
            return NULL;
        }
        total += list_sizes[i];
    }

    if (total == 0) {
        *total_elements = 0;
        *freq_values = NULL;
        *freq_counts = NULL;
        return NULL;
    }

    int hash_size = total * 2;
    if (hash_size < 16) {
        hash_size = 16;
    }

    HashTable *ht = create_hash_table(hash_size);
    if (ht == NULL) {
        *total_elements = 0;
        *freq_values = NULL;
        *freq_counts = NULL;
        return NULL;
    }

    for (int i = 0; i < num_lists; i++) {
        if (list_sizes[i] > 0 && list_of_lists[i] == NULL) {
            free_hash_table(ht, hash_size);
            *total_elements = 0;
            *freq_values = NULL;
            *freq_counts = NULL;
            return NULL;
        }
        for (int j = 0; j < list_sizes[i]; j++) {
            insert_or_increment(ht, list_of_lists[i][j], hash_size);
        }
    }

    int unique_count = 0;
    for (int i = 0; i < hash_size; i++) {
        Node *current = ht[i].head;
        while (current != NULL) {
            unique_count++;
            current = current->next;
        }
    }

    int *values = (int *)malloc(sizeof(int) * unique_count);
    int *counts = (int *)malloc(sizeof(int) * unique_count);
    if (values == NULL || counts == NULL) {
        free(values);
        free(counts);
        free_hash_table(ht, hash_size);
        *total_elements = 0;
        *freq_values = NULL;
        *freq_counts = NULL;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < hash_size && index < unique_count; i++) {
        Node *current = ht[i].head;
        while (current != NULL && index < unique_count) {
            values[index] = current->key;
            counts[index] = current->count;
            index++;
            current = current->next;
        }
    }

    int **result = (int **)malloc(sizeof(int *) * 2);
    if (result == NULL) {
        free(values);
        free(counts);
        free_hash_table(ht, hash_size);
        *total_elements = 0;
        *freq_values = NULL;
        *freq_counts = NULL;
        return NULL;
    }

    result[0] = values;
    result[1] = counts;

    *total_elements = unique_count;
    *freq_values = result[0];
    *freq_counts = result[1];

    free_hash_table(ht, hash_size);
    return result;
}

int main(void) {
    int sublist1[] = {1, 2, 3, 2};
    int sublist2[] = {3, 4, 1};
    int sublist3[] = {5, 5, 5};

    int *list_of_lists[] = {sublist1, sublist2, sublist3};
    /* Possible weaknesses found:
     *  Variable 'list_sizes' can be declared as const array [constVariable]
     */
    int list_sizes[] = {4, 3, 3};
    int num_lists = 3;

    int total_elements = 0;
    int *freq_values = NULL;
    int *freq_counts = NULL;

    int **result = frequency_of_elements(list_of_lists, list_sizes, num_lists,
                                         &total_elements, &freq_values, &freq_counts);

    if (result != NULL && total_elements > 0) {
        printf("Element frequencies:\n");
        for (int i = 0; i < total_elements; i++) {
            printf("%d: %d\n", freq_values[i], freq_counts[i]);
        }
        free(result[0]);
        free(result[1]);
        free(result);
    } else {
        printf("No elements processed or error occurred.\n");
    }

    return 0;
}