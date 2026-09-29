#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct {
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

static int dict_entry_init(DictEntry *entry, const char *key, int value)
{
    size_t key_len;

    if (entry == NULL || key == NULL) {
        return -1;
    }

    key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return -1;
    }

    memcpy(entry->key, key, key_len);
    entry->key[key_len] = '\0';
    entry->value = value;
    return 0;
}

static int contains(const int *arr, size_t count, int value)
{
    size_t i;

    if (arr == NULL) {
        return 0;
    }

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

    if (unique_count == NULL) {
        return NULL;
    }

    *unique_count = 0U;

    if (dict == NULL || dict_size == 0U) {
        return NULL;
    }

    if (dict_size > SIZE_MAX / sizeof(*unique)) {
        return NULL;
    }

    unique = malloc(dict_size * sizeof(*unique));
    if (unique == NULL) {
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
    static const struct {
        const char *key;
        int value;
    } input[] = {
        {"apple", 10},
        {"banana", 20},
        {"cherry", 10},
        {"date", 30},
        {"elderberry", 20},
        {"fig", 40}
    };
    size_t dict_size = sizeof(input) / sizeof(input[0]);
    DictEntry dict[sizeof(input) / sizeof(input[0])];
    size_t unique_count = 0U;
    size_t i;
    int *unique_values;

    for (i = 0; i < dict_size; i++) {
        if (dict_entry_init(&dict[i], input[i].key, input[i].value) != 0) {
            fprintf(stderr, "Invalid dictionary entry at index %zu\n", i);
            return EXIT_FAILURE;
        }
    }

    printf("Dictionary contents:\n");
    for (i = 0; i < dict_size; i++) {
        printf("  %s = %d\n", dict[i].key, dict[i].value);
    }

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