#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_VALUES 100
#define MAX_KEY_LEN 32

typedef struct {
    char key[MAX_KEY_LEN];
    int values[MAX_VALUES];
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

    memcpy(entry->key, key, len);
    entry->key[len] = '\0';
    return 0;
}

static int contains(const int *arr, size_t len, int value)
{
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int extract_unique_values(const DictEntry *dict, size_t entry_count,
                          int **result, size_t *result_count)
{
    size_t total = 0;
    size_t i;
    size_t j;
    size_t unique_count = 0;
    int *buffer = NULL;

    if (dict == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (i = 0; i < entry_count; i++) {
        if (dict[i].count > MAX_VALUES) {
            return -1;
        }
        if (total > SIZE_MAX - dict[i].count) {
            return -1;
        }
        total += dict[i].count;
    }

    if (total == 0) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    buffer = malloc(total * sizeof(int));
    if (buffer == NULL) {
        return -1;
    }

    for (i = 0; i < entry_count; i++) {
        for (j = 0; j < dict[i].count; j++) {
            if (!contains(buffer, unique_count, dict[i].values[j])) {
                if (unique_count >= total) {
                    free(buffer);
                    return -1;
                }
                buffer[unique_count] = dict[i].values[j];
                unique_count++;
            }
        }
    }

    qsort(buffer, unique_count, sizeof(int), compare_ints);

    *result = buffer;
    *result_count = unique_count;
    return 0;
}

int main(void)
{
    DictEntry dict[3];
    int *unique = NULL;
    size_t unique_count = 0;
    size_t i;
    int status;

    memset(dict, 0, sizeof(dict));

    if (set_key(&dict[0], "a") != 0) {
        fprintf(stderr, "Failed to set key\n");
        return EXIT_FAILURE;
    }
    dict[0].values[0] = 5;
    dict[0].values[1] = 7;
    dict[0].values[2] = 1;
    dict[0].count = 3;

    if (set_key(&dict[1], "b") != 0) {
        fprintf(stderr, "Failed to set key\n");
        return EXIT_FAILURE;
    }
    dict[1].values[0] = 7;
    dict[1].values[1] = 2;
    dict[1].values[2] = 5;
    dict[1].count = 3;

    if (set_key(&dict[2], "c") != 0) {
        fprintf(stderr, "Failed to set key\n");
        return EXIT_FAILURE;
    }
    dict[2].values[0] = 10;
    dict[2].values[1] = 1;
    dict[2].count = 2;

    status = extract_unique_values(dict, 3, &unique, &unique_count);
    if (status != 0) {
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