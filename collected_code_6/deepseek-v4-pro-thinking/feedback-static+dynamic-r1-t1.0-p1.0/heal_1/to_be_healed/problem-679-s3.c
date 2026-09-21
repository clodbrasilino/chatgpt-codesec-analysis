#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_DICT_SIZE 64
#define KEY_SIZE 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_SIZE];
    int value;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    size_t count;
} Dict;

int dict_add(Dict *dict, const char *key, int value) {
    if (dict == NULL || key == NULL || dict->count >= MAX_DICT_SIZE) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(key) >= KEY_SIZE) {
        return -1;
    }
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            dict->entries[i].value = value;
            return 0;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dict->entries[dict->count].key, key);
    dict->entries[dict->count].value = value;
    ++dict->count;
    return 0;
}

int dict_get_element_by_index(const Dict *dict, size_t index, const char **key, int *value) {
    if (dict == NULL || key == NULL || value == NULL || index >= dict->count) {
        return -1;
    }
    *key = dict->entries[index].key;
    *value = dict->entries[index].value;
    return 0;
}

int main(void) {
    Dict dict = {0};
    const char *key = NULL;
    int value = 0;

    if (dict_add(&dict, "one", 1) != 0 ||
        dict_add(&dict, "two", 2) != 0 ||
        dict_add(&dict, "three", 3) != 0) {
        return 1;
    }

    if (dict_get_element_by_index(&dict, 1, &key, &value) != 0) {
        return 1;
    }

    printf("%s: %d\n", key, value);
    return 0;
}