#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t size;
} Dict;

int *extract_unique_values(const Dict *dict, size_t *unique_count) {
    if (dict == NULL || dict->values == NULL || dict->size == 0 || unique_count == NULL) {
        *unique_count = 0;
        return NULL;
    }

    int *unique = malloc(dict->size * sizeof(int));
    if (unique == NULL) {
        *unique_count = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < dict->size; i++) {
        int found = 0;
        for (size_t j = 0; j < count; j++) {
            if (unique[j] == dict->values[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[count++] = dict->values[i];
        }
    }

    int *result = realloc(unique, count * sizeof(int));
    if (result == NULL && count > 0) {
        free(unique);
        *unique_count = 0;
        return NULL;
    }

    *unique_count = count;
    return result;
}

int main(void) {
    int values[] = {1, 2, 2, 3, 4, 4, 4, 5};
    Dict dict = {values, sizeof(values) / sizeof(values[0])};
    size_t unique_count = 0;

    int *unique = extract_unique_values(&dict, &unique_count);
    if (unique != NULL) {
        for (size_t i = 0; i < unique_count; i++) {
            printf("%d ", unique[i]);
        }
        printf("\n");
        free(unique);
    }

    return 0;
}