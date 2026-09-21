#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64
#define MAX_DICT_SIZE 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LENGTH];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    int size;
} Dictionary;

static bool safe_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    size_t src_len = strnlen(src, dest_size);
    /* Possible weaknesses found:
     *  If condition 'src_len>=dest_size' is true, the function will return/exit
     */
    if (src_len >= dest_size) {
        return false;
    }

    /* Possible weaknesses found:
     *  Identical condition 'src_len>=dest_size', second condition is always false [identicalConditionAfterEarlyExit]
     *  Testing identical condition 'src_len>=dest_size'
     */
    if (src_len >= dest_size) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return true;
}

static bool is_valid_dictionary(const Dictionary *dict) {
    return dict != NULL && dict->size > 0 && dict->size <= MAX_DICT_SIZE;
}

bool all_values_same(const Dictionary *dict) {
    if (!is_valid_dictionary(dict)) {
        return false;
    }

    const char *first_value = dict->entries[0].value;
    size_t first_len = strnlen(first_value, MAX_VALUE_LENGTH);

    if (first_len >= MAX_VALUE_LENGTH) {
        return false;
    }

    for (int i = 1; i < dict->size; i++) {
        const char *current_value = dict->entries[i].value;
        size_t current_len = strnlen(current_value, MAX_VALUE_LENGTH);

        if (current_len >= MAX_VALUE_LENGTH || first_len != current_len) {
            return false;
        }

        if (memcmp(first_value, current_value, first_len) != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    memset(&dict, 0, sizeof(dict));
    dict.size = 0;

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "a", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "b", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "c", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "d", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "different", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    return 0;
}