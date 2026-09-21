#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUP_STRING_MAX_LEN 4096

typedef struct ValueNode {
    char *value;
    struct ValueNode *next;
} ValueNode;

typedef struct DictEntry {
    char *key;
    ValueNode *values;
    size_t count;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
} Dict;

static size_t bounded_strnlen(const char *s, size_t max_len)
{
    size_t len;

    len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *dup_string(const char *s)
{
    size_t len;
    size_t buf_size;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = bounded_strnlen(s, DUP_STRING_MAX_LEN);
    if (len >= DUP_STRING_MAX_LEN) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  buf_size is assigned 'len+1' here.
     */
    buf_size = len + 1;
    copy = malloc(buf_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  Condition 'len+1>buf_size' is always false
     *  Condition 'len+1>buf_size' is always false [knownConditionTrueFalse]
     */
    if (len + 1 > buf_size) {
        free(copy);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len + 1);
    return copy;
}

void dict_init(Dict *dict)
{
    if (dict == NULL) {
        return;
    }
    dict->entries = NULL;
    dict->size = 0;
}

static DictEntry *dict_find(const Dict *dict, const char *key)
{
    DictEntry *entry;

    if (dict == NULL || key == NULL) {
        return NULL;
    }
    entry = dict->entries;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

int dict_add(Dict *dict, const char *key, const char *value)
{
    DictEntry *entry;
    ValueNode *node;
    ValueNode *tail;
    char *value_copy;
    char *key_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    value_copy = dup_string(value);
    if (value_copy == NULL) {
        return -1;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        free(value_copy);
        return -1;
    }
    node->value = value_copy;
    node->next = NULL;

    entry = dict_find(dict, key);
    if (entry != NULL) {
        if (entry->values == NULL) {
            entry->values = node;
        } else {
            tail = entry->values;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = node;
        }
        entry->count++;
        return 0;
    }

    key_copy = dup_string(key);
    if (key_copy == NULL) {
        free(node);
        free(value_copy);
        return -1;
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        free(key_copy);
        free(node);
        free(value_copy);
        return -1;
    }
    entry->key = key_copy;
    entry->values = node;
    entry->count = 1;
    entry->next = dict->entries;
    dict->entries = entry;
    dict->size++;
    return 0;
}

const ValueNode *dict_get(const Dict *dict, const char *key, size_t *count)
{
    DictEntry *entry;

    entry = dict_find(dict, key);
    if (entry == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }
    if (count != NULL) {
        *count = entry->count;
    }
    return entry->values;
}

void dict_free(Dict *dict)
{
    DictEntry *entry;
    DictEntry *next_entry;
    ValueNode *node;
    ValueNode *next_node;

    if (dict == NULL) {
        return;
    }
    entry = dict->entries;
    while (entry != NULL) {
        node = entry->values;
        while (node != NULL) {
            next_node = node->next;
            free(node->value);
            free(node);
            node = next_node;
        }
        next_entry = entry->next;
        free(entry->key);
        free(entry);
        entry = next_entry;
    }
    dict->entries = NULL;
    dict->size = 0;
}

int main(void)
{
    Dict dict;
    const char *keys[] = {"fruit", "color", "fruit", "color", "fruit", "vegetable"};
    const char *values[] = {"apple", "red", "banana", "blue", "cherry", "carrot"};
    size_t pair_count = sizeof(keys) / sizeof(keys[0]);
    size_t i;
    DictEntry *entry;
    ValueNode *node;

    dict_init(&dict);

    for (i = 0; i < pair_count; i++) {
        if (dict_add(&dict, keys[i], values[i]) != 0) {
            fprintf(stderr, "error: failed to add pair (%s, %s)\n", keys[i], values[i]);
            dict_free(&dict);
            return EXIT_FAILURE;
        }
    }

    entry = dict.entries;
    while (entry != NULL) {
        printf("%s: [", entry->key);
        node = entry->values;
        while (node != NULL) {
            printf("%s", node->value);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("]\n");
        entry = entry->next;
    }

    dict_free(&dict);
    return EXIT_SUCCESS;
}