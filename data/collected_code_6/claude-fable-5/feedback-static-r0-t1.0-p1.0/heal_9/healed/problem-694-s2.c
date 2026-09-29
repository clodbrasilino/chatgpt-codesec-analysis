#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define KEY_SIZE 32

typedef struct {
    char key[KEY_SIZE];
    int *values;
    size_t count;
} DictEntry;

static int set_key(DictEntry *entry, const char *key)
{
    size_t len;

    if (entry == NULL || key == NULL) {
        return -1;
    }

    len = strnlen(key, sizeof(entry->key));
    if (len >= sizeof(entry->key)) {
        return -1;
    }

    memmove(entry->key, key, len);
    entry->key[len] = '\0';

    return 0;
}

static int contains(const int *arr, size_t n, int value)
{
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

static int *extract_unique_values(const DictEntry *dict, size_t entry_count,
                                  size_t *unique_count)
{
    int *result;
    size_t total = 0;
    size_t i;
    size_t j;
    size_t found = 0;
    int *shrunk;

    if (dict == NULL || unique_count == NULL) {
        return NULL;
    }

    *unique_count = 0;

    for (i = 0; i < entry_count; i++) {
        if (dict[i].values == NULL && dict[i].count > 0) {
            return NULL;
        }
        if (dict[i].count > SIZE_MAX - total) {
            return NULL;
        }
        total += dict[i].count;
    }

    if (total == 0 || total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    result = malloc(total * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < entry_count; i++) {
        for (j = 0; j < dict[i].count; j++) {
            if (found < total && !contains(result, found, dict[i].values[j])) {
                result[found] = dict[i].values[j];
                found++;
            }
        }
    }

    if (found == 0) {
        free(result);
        return NULL;
    }

    shrunk = realloc(result, found * sizeof(int));
    if (shrunk != NULL) {
        result = shrunk;
    }

    *unique_count = found;
    return result;
}

int main(void)
{
    int values_a[] = {1, 2, 3, 4};
    int values_b[] = {3, 4, 5, 6};
    int values_c[] = {5, 6, 7, 8};
    DictEntry dict[3];
    int *unique;
    size_t unique_count = 0;
    size_t i;

    memset(dict, 0, sizeof(dict));

    if (set_key(&dict[0], "A") != 0) {
        fprintf(stderr, "Failed to set key\n");
        return EXIT_FAILURE;
    }
    dict[0].values = values_a;
    dict[0].count = sizeof(values_a) / sizeof(values_a[0]);

    if (set_key(&dict[1], "B") != 0) {
        fprintf(stderr, "Failed to set key\n");
        return EXIT_FAILURE;
    }
    dict[1].values = values_b;
    dict[1].count = sizeof(values_b) / sizeof(values_b[0]);

    if (set_key(&dict[2], "C") != 0) {
        fprintf(stderr, "Failed to set key\n");
        return EXIT_FAILURE;
    }
    dict[2].values = values_c;
    dict[2].count = sizeof(values_c) / sizeof(values_c[0]);

    unique = extract_unique_values(dict, 3, &unique_count);
    if (unique == NULL) {
        fprintf(stderr, "Failed to extract unique values\n");
        return EXIT_FAILURE;
    }

    printf("Unique values: ");
    for (i = 0; i < unique_count; i++) {
        printf("%d ", unique[i]);
    }
    printf("\n");

    free(unique);
    return EXIT_SUCCESS;
}