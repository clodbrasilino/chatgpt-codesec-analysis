#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[64];
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

int dict_init(Dict *dict, size_t capacity)
{
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

int dict_add(Dict *dict, const char *key, int value)
{
    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(key) >= sizeof(dict->entries[dict->size].key)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dict->entries[dict->size].key, key,
            sizeof(dict->entries[dict->size].key) - 1);
    dict->entries[dict->size].key[sizeof(dict->entries[dict->size].key) - 1] = '\0';
    dict->entries[dict->size].value = value;
    dict->size++;
    return 0;
}

int dict_sum(const Dict *dict, long *result)
{
    if (dict == NULL || result == NULL || dict->entries == NULL) {
        return -1;
    }
    long sum = 0;
    for (size_t i = 0; i < dict->size; i++) {
        sum += dict->entries[i].value;
    }
    *result = sum;
    return 0;
}

void dict_free(Dict *dict)
{
    if (dict != NULL) {
        free(dict->entries);
        dict->entries = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int main(void)
{
    Dict dict;
    long sum = 0;

    if (dict_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "apple", 10) != 0 ||
        dict_add(&dict, "banana", 20) != 0 ||
        dict_add(&dict, "cherry", 30) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (dict_sum(&dict, &sum) != 0) {
        fprintf(stderr, "Failed to compute sum\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Sum of all items: %ld\n", sum);

    dict_free(&dict);
    return EXIT_SUCCESS;
}