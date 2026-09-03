#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    const int *values;
    size_t value_count;
} DictEntry;

static int contains_value(const int *values, size_t count, int value) {
    size_t i;

    for (i = 0; i < count; i++) {
        if (values[i] == value) {
            return 1;
        }
    }

    return 0;
}

int extract_unique_values(const DictEntry *entries, size_t entry_count, int **out_values, size_t *out_count) {
    int *result = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i;
    size_t j;

    if (out_values == NULL || out_count == NULL) {
        if (out_values != NULL) {
            *out_values = NULL;
        }
        if (out_count != NULL) {
            *out_count = 0;
        }
        return -1;
    }

    *out_values = NULL;
    *out_count = 0;

    if (entry_count > 0 && entries == NULL) {
        return -1;
    }

    for (i = 0; i < entry_count; i++) {
        if (entries[i].value_count > 0 && entries[i].values == NULL) {
            free(result);
            return -1;
        }

        for (j = 0; j < entries[i].value_count; j++) {
            if (!contains_value(result, count, entries[i].values[j])) {
                if (count == capacity) {
                    size_t new_capacity;
                    int *temp;

                    if (capacity == 0) {
                        new_capacity = 4;
                    } else {
                        if (capacity > ((size_t)-1) / 2) {
                            free(result);
                            return -1;
                        }
                        new_capacity = capacity * 2;
                    }

                    if (new_capacity > ((size_t)-1) / sizeof(int)) {
                        free(result);
                        return -1;
                    }

                    temp = (int *)realloc(result, new_capacity * sizeof(int));
                    if (temp == NULL) {
                        free(result);
                        return -1;
                    }

                    result = temp;
                    capacity = new_capacity;
                }

                result[count] = entries[i].values[j];
                count++;
            }
        }
    }

    *out_values = result;
    *out_count = count;
    return 0;
}

int main(void) {
    int values1[] = {10, 20, 10, 30};
    int values2[] = {20, 40, 30, 50};
    /* Possible weaknesses found:
     *  Variable 'entries' can be declared as const array [constVariable]
     */
    DictEntry entries[] = {
        {"first", values1, 4},
        {"second", values2, 4}
    };
    int *unique = NULL;
    size_t unique_count = 0;
    size_t i;

    if (extract_unique_values(entries, 2, &unique, &unique_count) != 0) {
        return 1;
    }

    for (i = 0; i < unique_count; i++) {
        printf("%d ", unique[i]);
    }
    printf("\n");

    free(unique);
    return 0;
}