#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 256

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dict;

typedef int (*FilterFunc)(int value);

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t i = 0;
    while (i < maxlen && s[i] != '\0') {
        i++;
    }
    return i;
}

Dict *dict_create(size_t capacity)
{
    if (capacity == 0 || capacity > SIZE_MAX / sizeof(Entry)) {
        return NULL;
    }
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
    d->entries = malloc(capacity * sizeof(Entry));
    if (d->entries == NULL) {
        free(d);
        return NULL;
    }
    d->size = 0;
    d->capacity = capacity;
    return d;
}

int dict_add(Dict *d, const char *key, int value)
{
    if (d == NULL || key == NULL) {
        return -1;
    }
    if (d->size >= d->capacity) {
        if (d->capacity > SIZE_MAX / 2 / sizeof(Entry)) {
            return -1;
        }
        size_t new_capacity = d->capacity * 2;
        Entry *tmp = realloc(d->entries, new_capacity * sizeof(Entry));
        if (tmp == NULL) {
            return -1;
        }
        d->entries = tmp;
        d->capacity = new_capacity;
    }
    size_t len = safe_strnlen(key, MAX_KEY_LEN);
    if (len >= MAX_KEY_LEN) {
        return -1;
    }
    /* Possible weaknesses found:
     *  dest_size is assigned 'len+1' here.
     */
    size_t dest_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'dest_size<len' is always false [knownConditionTrueFalse]
     *  Condition 'dest_size<len' is always false
     */
    if (dest_size < len) {
        return -1;
    }
    char *key_copy = malloc(dest_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (key_copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     *  Condition 'len<dest_size' is always true
     *  Condition 'len<dest_size' is always true [knownConditionTrueFalse]
     */
    if (len > 0 && len < dest_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(key_copy, key, len);
    }
    key_copy[len] = '\0';
    d->entries[d->size].key = key_copy;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

void dict_destroy(Dict *d)
{
    if (d == NULL) {
        return;
    }
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
    }
    free(d->entries);
    free(d);
}

Dict *dict_filter(const Dict *d, FilterFunc predicate)
{
    if (d == NULL || predicate == NULL) {
        return NULL;
    }
    Dict *result = dict_create(d->capacity);
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < d->size; i++) {
        if (predicate(d->entries[i].value)) {
            if (dict_add(result, d->entries[i].key, d->entries[i].value) != 0) {
                dict_destroy(result);
                return NULL;
            }
        }
    }
    return result;
}

void dict_print(const Dict *d)
{
    if (d == NULL) {
        return;
    }
    printf("{");
    for (size_t i = 0; i < d->size; i++) {
        printf("\"%s\": %d", d->entries[i].key, d->entries[i].value);
        if (i + 1 < d->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int is_positive(int value)
{
    return value > 0;
}

int main(void)
{
    Dict *d = dict_create(4);
    if (d == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(d, "apple", 10) != 0 ||
        dict_add(d, "banana", -5) != 0 ||
        dict_add(d, "cherry", 7) != 0 ||
        dict_add(d, "date", 0) != 0 ||
        dict_add(d, "elderberry", 3) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    printf("Original dictionary:\n");
    dict_print(d);

    Dict *filtered = dict_filter(d, is_positive);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to filter dictionary\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    printf("Filtered dictionary (positive values):\n");
    dict_print(filtered);

    dict_destroy(filtered);
    dict_destroy(d);
    return EXIT_SUCCESS;
}