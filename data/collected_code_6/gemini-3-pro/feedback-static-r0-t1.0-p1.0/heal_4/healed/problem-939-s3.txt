#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} Dictionary;

int compare_dicts(const void *a, const void *b) {
    const Dictionary *dictA = (const Dictionary *)a;
    const Dictionary *dictB = (const Dictionary *)b;
    if (dictA->key == NULL || dictB->key == NULL) return 0;
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
    
    size_t len = 0;
    while (len < MAX_STR_LEN - 1 && src[len] != '\0') {
        len++;
    }
    
    char *dest = (char *)malloc(len + 1);
    if (dest != NULL) {
        for (size_t i = 0; i < len; i++) {
            dest[i] = src[i];
        }
        dest[len] = '\0';
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
        if (list[i].key != NULL && list[i].value != NULL) {
            printf("%s: %s\n", list[i].key, list[i].value);
        }
    }

    for (size_t i = 0; i < num_dicts; i++) {
        free(list[i].key);
        free(list[i].value);
    }
    free(list);

    return EXIT_SUCCESS;
}