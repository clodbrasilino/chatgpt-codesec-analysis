#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Dictionary;

int compare_dicts(const void *a, const void *b) {
    const Dictionary *dictA = (const Dictionary *)a;
    const Dictionary *dictB = (const Dictionary *)b;
    return strcmp(dictA->key, dictB->key);
}

void sort_dictionaries(Dictionary *list, size_t count) {
    if (list == NULL || count == 0) {
        return;
    }
    qsort(list, count, sizeof(Dictionary), compare_dicts);
}

char* create_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    size_t len = strlen(src) + 1;
    char *dest = (char *)malloc(len);
    if (dest != NULL) {
        memcpy(dest, src, len);
    }
    return dest;
}

int main(void) {
    size_t num_dicts = 3;
    Dictionary *list = (Dictionary *)malloc(num_dicts * sizeof(Dictionary));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0].key = create_string("cherry");
    list[0].value = create_string("red");

    list[1].key = create_string("apple");
    list[1].value = create_string("green");

    list[2].key = create_string("banana");
    list[2].value = create_string("yellow");

    sort_dictionaries(list, num_dicts);

    for (size_t i = 0; i < num_dicts; i++) {
        printf("%s: %s\n", list[i].key, list[i].value);
    }

    for (size_t i = 0; i < num_dicts; i++) {
        free(list[i].key);
        free(list[i].value);
    }
    free(list);

    return EXIT_SUCCESS;
}