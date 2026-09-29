#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 64

typedef struct {
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

static int contains(const int *arr, size_t count, int value)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

static int *extract_unique_values(const DictEntry *dict, size_t dict_size, size_t *unique_count)
{
    int *unique;
    size_t i;
    size_t count;

    if (dict == NULL || unique_count == NULL || dict_size == 0U) {
        if (unique_count != NULL) {
            *unique_count = 0U;
        }
        return NULL;
    }

    unique = malloc(dict_size * sizeof(*unique));
    if (unique == NULL) {
        *unique_count = 0U;
        return NULL;
    }

    count = 0U;
    for (i = 0; i < dict_size; i++) {
        if (!contains(unique, count, dict[i].value)) {
            unique[count] = dict[i].value;
            count++;
        }
    }

    *unique_count = count;
    return unique;
}

int main(void)
{
    DictEntry dict[] = {
        {"apple", 10},
        {"banana", 20},
        {"cherry", 10},
        {"date", 30},
        {"elderberry", 20},
        {"fig", 40}
    };
    size_t dict_size = sizeof(dict) / sizeof(dict[0]);
    size_t unique_count = 0U;
    size_t i;
    int *unique_values;

    unique_values = extract_unique_values(dict, dict_size, &unique_count);
    if (unique_values == NULL) {
        fprintf(stderr, "Failed to extract unique values\n");
        return EXIT_FAILURE;
    }

    printf("Unique values:");
    for (i = 0; i < unique_count; i++) {
        printf(" %d", unique_values[i]);
    }
    printf("\n");

    free(unique_values);
    return EXIT_SUCCESS;
}