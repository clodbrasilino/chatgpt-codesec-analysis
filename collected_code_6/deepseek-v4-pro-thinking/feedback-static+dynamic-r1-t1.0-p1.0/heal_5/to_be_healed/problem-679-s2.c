#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define DICT_CAPACITY 32
#define KEY_LENGTH 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_LENGTH];
    int value;
} dict_entry_t;

typedef struct {
    dict_entry_t entries[DICT_CAPACITY];
    size_t size;
} dict_t;

static size_t safe_strnlen(const char *s, size_t max_len) {
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            break;
        }
    }
    return i;
}

int dict_set_entry(dict_t *dict, const char *key, int value) {
    if (dict == NULL || key == NULL || dict->size >= DICT_CAPACITY) {
        return -1;
    }
    size_t key_len = safe_strnlen(key, KEY_LENGTH);
    if (key_len == KEY_LENGTH) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->entries[dict->size].key, key, key_len + 1);
    dict->entries[dict->size].value = value;
    dict->size++;
    return 0;
}

const char *dict_get_key_at_index(const dict_t *dict, size_t index) {
    if (dict == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].key;
}

int dict_get_value_at_index(const dict_t *dict, size_t index, int *value) {
    if (dict == NULL || index >= dict->size || value == NULL) {
        return -1;
    }
    *value = dict->entries[index].value;
    return 0;
}

int main(void) {
    dict_t dict = { .size = 0 };

    dict_set_entry(&dict, "alpha", 10);
    dict_set_entry(&dict, "beta", 20);
    dict_set_entry(&dict, "gamma", 30);

    const char *key = dict_get_key_at_index(&dict, 1);
    if (key != NULL) {
        printf("%s\n", key);
    }

    int val;
    if (dict_get_value_at_index(&dict, 1, &val) == 0) {
        printf("%d\n", val);
    }

    return 0;
}