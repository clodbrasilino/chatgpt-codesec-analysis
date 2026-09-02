#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ValueHash {
    int value;
    struct ValueHash *next, *prev;
};

bool add_value(struct ValueHash **table, int value) {
    struct ValueHash *s = *table;
    while (s != NULL && s->value != value) {
        s = s->next;
    }
    if (s == NULL) {
        s = (struct ValueHash *)malloc(sizeof(struct ValueHash));
        if (s == NULL) return false;
        s->value = value;
        s->next = *table;
        if (*table != NULL) (*table)->prev = s;
        *table = s;
        s->prev = NULL;
        return true;
    }
    return false;
}

void free_table(struct ValueHash **table) {
    struct ValueHash *current = *table, *tmp;
    while (current != NULL) {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    *table = NULL;
}

int* extract_unique_values(int** dict, int dictSize, const int* dictColSize, int* returnSize) {
    struct ValueHash *table = NULL;
    for (int i = 0; i < dictSize; i++) {
        for (int j = 0; j < dictColSize[i]; j++) {
            add_value(&table, dict[i][j]);
        }
    }

    struct ValueHash *s = table;
    while (s != NULL) {
        ++(*returnSize);
        s = s->next;
    }

    int *result = (int*)malloc(*returnSize * sizeof(int));
    if (result == NULL) return NULL;

    int index = 0;
    s = table;
    while (s != NULL) {
        result[index++] = s->value;
        s = s->next;
    }

    free_table(&table);
    return result;
}

int main() {
    int dict[][5] = {{1, 2, 2, 3}, {4, 5, 1}, {6, 7, 8, 9, 2}};
    int dictSize = 3;
    const int dictColSize[] = {4, 3, 5};
    int returnSize = 0;
    int *uniqueValues = extract_unique_values((int**)dict, dictSize, dictColSize, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", uniqueValues[i]);
    }
    free(uniqueValues);
    return 0;
}