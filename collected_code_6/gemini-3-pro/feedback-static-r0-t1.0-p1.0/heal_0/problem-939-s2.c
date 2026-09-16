#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} Dictionary;

int compare_dicts(const void *a, const void *b) {
    const Dictionary *dict_a = (const Dictionary *)a;
    const Dictionary *dict_b = (const Dictionary *)b;
    return strcmp(dict_a->key, dict_b->key);
}

void sort_dictionaries(Dictionary *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }
    qsort(list, size, sizeof(Dictionary), compare_dicts);
}

void free_dictionaries(Dictionary *list, size_t size) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(list[i].key);
    }
    free(list);
}

int main(void) {
    size_t num_dicts = 3;
    Dictionary *list = malloc(num_dicts * sizeof(Dictionary));
    
    if (list == NULL) {
        return 1;
    }

    list[0].key = strdup("zebra");
    list[0].value = 10;
    
    list[1].key = strdup("apple");
    list[1].value = 20;
    
    list[2].key = strdup("monkey");
    list[2].value = 30;

    for (size_t i = 0; i < num_dicts; i++) {
        if (list[i].key == NULL) {
            free_dictionaries(list, num_dicts);
            return 1;
        }
    }

    sort_dictionaries(list, num_dicts);

    for (size_t i = 0; i < num_dicts; i++) {
        printf("%s: %d\n", list[i].key, list[i].value);
    }

    free_dictionaries(list, num_dicts);

    return 0;
}