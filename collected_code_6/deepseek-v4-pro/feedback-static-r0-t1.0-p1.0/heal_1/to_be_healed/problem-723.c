#include <stdio.h>
#include <stdlib.h>

typedef struct Pair {
    int first;
    int second;
    int count;
    struct Pair *next;
} Pair;

unsigned long hash_pair(int first, int second) {
    unsigned long h = 5381;
    h = ((h << 5) + h) + first;
    h = ((h << 5) + h) + second;
    return h;
}

Pair *find_pair(Pair **table, int table_size, int first, int second) {
    unsigned long index = hash_pair(first, second) % table_size;
    Pair *current = table[index];
    while (current != NULL) {
        if (current->first == first && current->second == second) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int insert_pair(Pair **table, int table_size, int first, int second) {
    unsigned long index = hash_pair(first, second) % table_size;
    Pair *existing = find_pair(table, table_size, first, second);
    if (existing != NULL) {
        existing->count++;
        return 0;
    }
    Pair *new_pair = (Pair *)malloc(sizeof(Pair));
    if (new_pair == NULL) {
        return -1;
    }
    new_pair->first = first;
    new_pair->second = second;
    new_pair->count = 1;
    new_pair->next = table[index];
    table[index] = new_pair;
    return 0;
}

void free_table(Pair **table, int table_size) {
    for (int i = 0; i < table_size; i++) {
        Pair *current = table[i];
        while (current != NULL) {
            Pair *next = current->next;
            free(current);
            current = next;
        }
    }
    free(table);
}

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int count_same_pairs(int *list1, int size1, int *list2, int size2) {
    if (list1 == NULL || list2 == NULL || size1 <= 0 || size2 <= 0 || size1 % 2 != 0 || size2 % 2 != 0) {
        return -1;
    }
    int table_size = 1024;
    Pair **table = (Pair **)calloc(table_size, sizeof(Pair *));
    if (table == NULL) {
        return -1;
    }
    for (int i = 0; i < size1; i += 2) {
        if (insert_pair(table, table_size, list1[i], list1[i + 1]) != 0) {
            free_table(table, table_size);
            return -1;
        }
    }
    int total_count = 0;
    for (int i = 0; i < size2; i += 2) {
        /* Possible weaknesses found:
         *  Variable 'found' can be declared as pointer to const [constVariablePointer]
         */
        Pair *found = find_pair(table, table_size, list2[i], list2[i + 1]);
        if (found != NULL) {
            total_count += found->count;
        }
    }
    free_table(table, table_size);
    return total_count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 1, 2, 5, 6};
    int list2[] = {1, 2, 7, 8, 1, 2, 3, 4};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result = count_same_pairs(list1, size1, list2, size2);
    if (result == -1) {
        printf("Error in input or memory allocation\n");
        return 1;
    }
    printf("Count of same pairs: %d\n", result);
    return 0;
}