#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->items = malloc(capacity * sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void dict_destroy(Dictionary *dict) {
    if (dict) {
        free(dict->items);
        free(dict);
    }
}

int dict_insert(Dictionary *dict, int key, int value) {
    if (!dict || dict->size >= dict->capacity) return -1;
    dict->items[dict->size].key = key;
    dict->items[dict->size].value = value;
    dict->size++;
    return 0;
}

long long dict_sum_values(const Dictionary *dict) {
    long long sum = 0;
    if (!dict) return 0;
    for (size_t i = 0; i < dict->size; i++) {
        sum += dict->items[i].value;
    }
    return sum;
}

int main(void) {
    Dictionary *dict = dict_create(3);
    if (!dict) {
        fprintf(stderr, "Failed to allocate dictionary\n");
        return 1;
    }

    if (dict_insert(dict, 1, 10) != 0 ||
        dict_insert(dict, 2, 20) != 0 ||
        dict_insert(dict, 3, 30) != 0) {
        fprintf(stderr, "Failed to insert into dictionary\n");
        dict_destroy(dict);
        return 1;
    }

    long long total = dict_sum_values(dict);
    printf("%lld\n", total);

    dict_destroy(dict);
    return 0;
}