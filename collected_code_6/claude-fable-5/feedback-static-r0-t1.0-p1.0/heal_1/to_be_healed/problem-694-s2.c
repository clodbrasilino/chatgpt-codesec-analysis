#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[32];
    int *values;
    size_t count;
} DictEntry;

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
            if (!contains(result, found, dict[i].values[j])) {
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

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strncpy(dict[0].key, "A", sizeof(dict[0].key) - 1);
    dict[0].values = values_a;
    dict[0].count = sizeof(values_a) / sizeof(values_a[0]);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strncpy(dict[1].key, "B", sizeof(dict[1].key) - 1);
    dict[1].values = values_b;
    dict[1].count = sizeof(values_b) / sizeof(values_b[0]);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strncpy(dict[2].key, "C", sizeof(dict[2].key) - 1);
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