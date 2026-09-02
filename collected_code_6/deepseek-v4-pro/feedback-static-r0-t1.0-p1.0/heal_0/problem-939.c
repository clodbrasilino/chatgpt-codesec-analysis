#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 16
#define MAX_STRING_LEN 64

typedef struct {
    char keys[MAX_KEYS][MAX_STRING_LEN];
    char values[MAX_KEYS][MAX_STRING_LEN];
    int key_count;
} Dict;

typedef struct {
    Dict *dicts;
    int count;
    int capacity;
} DictList;

typedef int (*cmp_fn)(const Dict*, const Dict*, const char*);

int compare_by_key_str(const Dict *a, const Dict *b, const char *key) {
    const char *va = "";
    const char *vb = "";
    int i;

    for (i = 0; i < a->key_count; i++) {
        if (strcmp(a->keys[i], key) == 0) {
            va = a->values[i];
            break;
        }
    }

    for (i = 0; i < b->key_count; i++) {
        if (strcmp(b->keys[i], key) == 0) {
            vb = b->values[i];
            break;
        }
    }

    return strcmp(va, vb);
}

int compare_by_key_int(const Dict *a, const Dict *b, const char *key) {
    const char *va = "0";
    const char *vb = "0";
    int ia, ib;
    int i;

    for (i = 0; i < a->key_count; i++) {
        if (strcmp(a->keys[i], key) == 0) {
            va = a->values[i];
            break;
        }
    }

    for (i = 0; i < b->key_count; i++) {
        if (strcmp(b->keys[i], key) == 0) {
            vb = b->values[i];
            break;
        }
    }

    ia = atoi(va);
    ib = atoi(vb);

    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

void dictlist_init(DictList *list, int initial_capacity) {
    if (initial_capacity < 1) initial_capacity = 1;
    list->dicts = (Dict*)malloc((size_t)initial_capacity * sizeof(Dict));
    if (list->dicts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    list->count = 0;
    list->capacity = initial_capacity;
}

void dictlist_free(DictList *list) {
    if (list->dicts != NULL) {
        free(list->dicts);
        list->dicts = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

void dictlist_add(DictList *list, const Dict *dict) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Dict *new_dicts = (Dict*)realloc(list->dicts, (size_t)new_capacity * sizeof(Dict));
        if (new_dicts == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        list->dicts = new_dicts;
        list->capacity = new_capacity;
    }

    list->dicts[list->count] = *dict;
    list->count++;
}

void swap_dict(Dict *a, Dict *b) {
    Dict temp = *a;
    *a = *b;
    *b = temp;
}

void sort_dict_list(DictList *list, const char *sort_key, int is_numeric) {
    int i, j;
    cmp_fn cmp = is_numeric ? compare_by_key_int : compare_by_key_str;

    if (list->count <= 1) return;

    for (i = 0; i < list->count - 1; i++) {
        for (j = 0; j < list->count - 1 - i; j++) {
            if (cmp(&list->dicts[j], &list->dicts[j + 1], sort_key) > 0) {
                swap_dict(&list->dicts[j], &list->dicts[j + 1]);
            }
        }
    }
}

void dict_init(Dict *dict) {
    dict->key_count = 0;
}

void dict_set(Dict *dict, const char *key, const char *value) {
    int i;

    for (i = 0; i < dict->key_count; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            strncpy(dict->values[i], value, MAX_STRING_LEN - 1);
            dict->values[i][MAX_STRING_LEN - 1] = '\0';
            return;
        }
    }

    if (dict->key_count < MAX_KEYS) {
        strncpy(dict->keys[dict->key_count], key, MAX_STRING_LEN - 1);
        dict->keys[dict->key_count][MAX_STRING_LEN - 1] = '\0';
        strncpy(dict->values[dict->key_count], value, MAX_STRING_LEN - 1);
        dict->values[dict->key_count][MAX_STRING_LEN - 1] = '\0';
        dict->key_count++;
    }
}

void print_dict_list(const DictList *list) {
    int i, j;

    for (i = 0; i < list->count; i++) {
        printf("{");
        for (j = 0; j < list->dicts[i].key_count; j++) {
            if (j > 0) printf(", ");
            printf("\"%s\": \"%s\"", list->dicts[i].keys[j], list->dicts[i].values[j]);
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