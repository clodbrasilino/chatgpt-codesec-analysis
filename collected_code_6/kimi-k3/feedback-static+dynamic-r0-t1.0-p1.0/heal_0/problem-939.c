#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *dicts;
    size_t size;
    size_t capacity;
} DictList;

int dict_init(Dictionary *d, size_t initial_capacity) {
    if (d == NULL || initial_capacity == 0) {
        return -1;
    }
    d->entries = malloc(initial_capacity * sizeof(Entry));
    if (d->entries == NULL) {
        return -1;
    }
    d->size = 0;
    d->capacity = initial_capacity;
    return 0;
}

int dict_add(Dictionary *d, const char *key, const char *value) {
    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    
    if (d->size >= d->capacity) {
        size_t new_capacity = d->capacity * 2;
        Entry *new_entries = realloc(d->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return -1;
        }
        d->entries = new_entries;
        d->capacity = new_capacity;
    }
    
    d->entries[d->size].key = malloc(strlen(key) + 1);
    if (d->entries[d->size].key == NULL) {
        return -1;
    }
    strcpy(d->entries[d->size].key, key);
    
    d->entries[d->size].value = malloc(strlen(value) + 1);
    if (d->entries[d->size].value == NULL) {
        free(d->entries[d->size].key);
        return -1;
    }
    strcpy(d->entries[d->size].value, value);
    
    d->size++;
    return 0;
}

const char *dict_get(const Dictionary *d, const char *key) {
    if (d == NULL || key == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            return d->entries[i].value;
        }
    }
    return NULL;
}

void dict_free(Dictionary *d) {
    if (d == NULL) {
        return;
    }
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

int dictlist_init(DictList *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    list->dicts = malloc(initial_capacity * sizeof(Dictionary));
    if (list->dicts == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return 0;
}

int dictlist_add(DictList *list, Dictionary *d) {
    if (list == NULL || d == NULL) {
        return -1;
    }
    
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Dictionary *new_dicts = realloc(list->dicts, new_capacity * sizeof(Dictionary));
        if (new_dicts == NULL) {
            return -1;
        }
        list->dicts = new_dicts;
        list->capacity = new_capacity;
    }
    
    list->dicts[list->size] = *d;
    list->size++;
    return 0;
}

void dictlist_free(DictList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->size; i++) {
        dict_free(&list->dicts[i]);
    }
    free(list->dicts);
    list->dicts = NULL;
    list->size = 0;
    list->capacity = 0;
}

int compare_dicts(const void *a, const void *b, void *context) {
    const Dictionary *da = (const Dictionary *)a;
    const Dictionary *db = (const Dictionary *)b;
    const char *sort_key = (const char *)context;
    
    const char *va = dict_get(da, sort_key);
    const char *vb = dict_get(db, sort_key);
    
    if (va == NULL && vb == NULL) {
        return 0;
    }
    if (va == NULL) {
        return 1;
    }
    if (vb == NULL) {
        return -1;
    }
    
    return strcmp(va, vb);
}

int sort_dict_list(DictList *list, const char *sort_key) {
    if (list == NULL || sort_key == NULL || list->size == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < list->size - 1; i++) {
        for (size_t j = 0; j < list->size - i - 1; j++) {
            if (compare_dicts(&list->dicts[j], &list->dicts[j + 1], (void *)sort_key) > 0) {
                Dictionary temp = list->dicts[j];
                list->dicts[j] = list->dicts[j + 1];
                list->dicts[j + 1] = temp;
            }
        }
    }
    return 0;
}

void print_dict(const Dictionary *d) {
    if (d == NULL) {
        printf("NULL\n");
        return;
    }
    printf("{");
    for (size_t i = 0; i < d->size; i++) {
        printf("\"%s\": \"%s\"", d->entries[i].key, d->entries[i].value);
        if (i < d->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void print_dict_list(const DictList *list) {
    if (list == NULL) {
        printf("NULL\n");
        return;
    }
    for (size_t i = 0; i < list->size; i++) {
        print_dict(&list->dicts[i]);
    }
}

int main(void) {
    DictList list;
    Dictionary d1, d2, d3;
    
    if (dictlist_init(&list, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary list\n");
        return EXIT_FAILURE;
    }
    
    if (dict_init(&d1, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary 1\n");
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    if (dict_init(&d2, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary 2\n");
        dict_free(&d1);
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    if (dict_init(&d3, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary 3\n");
        dict_free(&d1);
        dict_free(&d2);
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    if (dict_add(&d1, "name", "Charlie") != 0 ||
        dict_add(&d1, "age", "35") != 0 ||
        dict_add(&d1, "city", "New York") != 0) {
        fprintf(stderr, "Failed to add entries to dictionary 1\n");
        dict_free(&d1);
        dict_free(&d2);
        dict_free(&d3);
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    if (dict_add(&d2, "name", "Alice") != 0 ||
        dict_add(&d2, "age", "28") != 0 ||
        dict_add(&d2, "city", "Boston") != 0) {
        fprintf(stderr, "Failed to add entries to dictionary 2\n");
        dict_free(&d1);
        dict_free(&d2);
        dict_free(&d3);
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    if (dict_add(&d3, "name", "Bob") != 0 ||
        dict_add(&d3, "age", "42") != 0 ||
        dict_add(&d3, "city", "Chicago") != 0) {
        fprintf(stderr, "Failed to add entries to dictionary 3\n");
        dict_free(&d1);
        dict_free(&d2);
        dict_free(&d3);
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    if (dictlist_add(&list, &d1) != 0 ||
        dictlist_add(&list, &d2) != 0 ||
        dictlist_add(&list, &d3) != 0) {
        fprintf(stderr, "Failed to add dictionaries to list\n");
        dict_free(&d1);
        dict_free(&d2);
        dict_free(&d3);
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    printf("Before sorting:\n");
    print_dict_list(&list);
    
    if (sort_dict_list(&list, "name") != 0) {
        fprintf(stderr, "Failed to sort dictionary list\n");
        dictlist_free(&list);
        return EXIT_FAILURE;
    }
    
    printf("\nAfter sorting by name:\n");
    print_dict_list(&list);
    
    dictlist_free(&list);
    
    return EXIT_SUCCESS;
}