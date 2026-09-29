#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_KEYS 16
#define MAX_STRING_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char keys[MAX_KEYS][MAX_STRING_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char values[MAX_KEYS][MAX_STRING_LEN];
    int key_count;
} Dict;

typedef struct {
    Dict *dicts;
    int count;
    int capacity;
} DictList;

typedef int (*cmp_fn)(const Dict*, const Dict*, const char*);

static size_t safe_strnlen(const char *str, size_t maxlen) {
    size_t i;
    if (str == NULL) return 0;
    for (i = 0; i < maxlen && str[i] != '\0'; i++);
    return i;
}

static void safe_str_copy(char *dest, const char *src, size_t dest_size) {
    size_t i;
    if (dest == NULL || dest_size == 0) return;
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

static int safe_str_to_int(const char *str, int *out) {
    char *endptr;
    long val;

    if (str == NULL || out == NULL) return 0;

    errno = 0;
    val = strtol(str, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    *out = (int)val;
    return 1;
}

int compare_by_key_str(const Dict *a, const Dict *b, const char *key) {
    const char *va = "";
    const char *vb = "";
    int i;

    if (a == NULL || b == NULL || key == NULL) return 0;

    for (i = 0; i < a->key_count && i < MAX_KEYS; i++) {
        if (strncmp(a->keys[i], key, MAX_STRING_LEN - 1) == 0) {
            va = a->values[i];
            break;
        }
    }

    for (i = 0; i < b->key_count && i < MAX_KEYS; i++) {
        if (strncmp(b->keys[i], key, MAX_STRING_LEN - 1) == 0) {
            vb = b->values[i];
            break;
        }
    }

    return strncmp(va, vb, MAX_STRING_LEN - 1);
}

int compare_by_key_int(const Dict *a, const Dict *b, const char *key) {
    const char *va = "0";
    const char *vb = "0";
    int ia = 0, ib = 0;
    int i;

    if (a == NULL || b == NULL || key == NULL) return 0;

    for (i = 0; i < a->key_count && i < MAX_KEYS; i++) {
        if (strncmp(a->keys[i], key, MAX_STRING_LEN - 1) == 0) {
            va = a->values[i];
            break;
        }
    }

    for (i = 0; i < b->key_count && i < MAX_KEYS; i++) {
        if (strncmp(b->keys[i], key, MAX_STRING_LEN - 1) == 0) {
            vb = b->values[i];
            break;
        }
    }

    if (!safe_str_to_int(va, &ia)) {
        ia = 0;
    }
    if (!safe_str_to_int(vb, &ib)) {
        ib = 0;
    }

    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

void dictlist_init(DictList *list, int initial_capacity) {
    if (list == NULL) return;
    if (initial_capacity < 1) initial_capacity = 1;
    if (initial_capacity > 1024) initial_capacity = 1024;
    list->dicts = (Dict*)malloc((size_t)initial_capacity * sizeof(Dict));
    if (list->dicts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    list->count = 0;
    list->capacity = initial_capacity;
}

void dictlist_free(DictList *list) {
    if (list == NULL) return;
    if (list->dicts != NULL) {
        free(list->dicts);
        list->dicts = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

void dictlist_add(DictList *list, const Dict *dict) {
    if (list == NULL || dict == NULL) return;
    if (list->count >= list->capacity) {
        int new_capacity;
        Dict *new_dicts;
        if (list->capacity > 512) return;
        new_capacity = list->capacity * 2;
        if (new_capacity < 1) new_capacity = 1;
        if (new_capacity > 1024) new_capacity = 1024;
        new_dicts = (Dict*)realloc(list->dicts, (size_t)new_capacity * sizeof(Dict));
        if (new_dicts == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        list->dicts = new_dicts;
        list->capacity = new_capacity;
    }

    if (list->count < list->capacity) {
        list->dicts[list->count] = *dict;
        list->count++;
    }
}

void swap_dict(Dict *a, Dict *b) {
    Dict temp;
    if (a == NULL || b == NULL) return;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort_dict_list(DictList *list, const char *sort_key, int is_numeric) {
    int i, j;
    cmp_fn cmp;

    if (list == NULL || sort_key == NULL) return;
    if (list->count <= 1) return;

    cmp = is_numeric ? compare_by_key_int : compare_by_key_str;

    for (i = 0; i < list->count - 1; i++) {
        for (j = 0; j < list->count - 1 - i; j++) {
            if (cmp(&list->dicts[j], &list->dicts[j + 1], sort_key) > 0) {
                swap_dict(&list->dicts[j], &list->dicts[j + 1]);
            }
        }
    }
}

void dict_init(Dict *dict) {
    if (dict == NULL) return;
    dict->key_count = 0;
    memset(dict->keys, 0, sizeof(dict->keys));
    memset(dict->values, 0, sizeof(dict->values));
}

void dict_set(Dict *dict, const char *key, const char *value) {
    int i;
    size_t key_len;
    size_t value_len;

    if (dict == NULL || key == NULL || value == NULL) return;

    key_len = safe_strnlen(key, MAX_STRING_LEN);
    if (key_len >= MAX_STRING_LEN) return;

    value_len = safe_strnlen(value, MAX_STRING_LEN);
    if (value_len >= MAX_STRING_LEN) return;

    for (i = 0; i < dict->key_count && i < MAX_KEYS; i++) {
        if (strncmp(dict->keys[i], key, MAX_STRING_LEN - 1) == 0) {
            safe_str_copy(dict->values[i], value, MAX_STRING_LEN);
            return;
        }
    }

    if (dict->key_count < MAX_KEYS) {
        safe_str_copy(dict->keys[dict->key_count], key, MAX_STRING_LEN);
        safe_str_copy(dict->values[dict->key_count], value, MAX_STRING_LEN);
        dict->key_count++;
    }
}

void print_dict_list(const DictList *list) {
    int i, j;

    if (list == NULL) return;

    for (i = 0; i < list->count; i++) {
        printf("{");
        for (j = 0; j < list->dicts[i].key_count && j < MAX_KEYS; j++) {
            if (j > 0) printf(", ");
            printf("\"%.63s\": \"%.63s\"", list->dicts[i].keys[j], list->dicts[i].values[j]);
        }
        printf("}\n");
    }
}

int main(void) {
    DictList list;
    Dict dict1, dict2, dict3;

    dictlist_init(&list, 2);

    dict_init(&dict1);
    dict_set(&dict1, "name", "Charlie");
    dict_set(&dict1, "age", "35");
    dict_set(&dict1, "score", "88");
    dictlist_add(&list, &dict1);

    dict_init(&dict2);
    dict_set(&dict2, "name", "Alice");
    dict_set(&dict2, "age", "25");
    dict_set(&dict2, "score", "95");
    dictlist_add(&list, &dict2);

    dict_init(&dict3);
    dict_set(&dict3, "name", "Bob");
    dict_set(&dict3, "age", "30");
    dict_set(&dict3, "score", "75");
    dictlist_add(&list, &dict3);

    printf("Original list:\n");
    print_dict_list(&list);

    sort_dict_list(&list, "name", 0);
    printf("\nSorted by name:\n");
    print_dict_list(&list);

    sort_dict_list(&list, "age", 1);
    printf("\nSorted by age (numeric):\n");
    print_dict_list(&list);

    sort_dict_list(&list, "score", 1);
    printf("\nSorted by score (numeric):\n");
    print_dict_list(&list);

    dictlist_free(&list);

    return 0;
}