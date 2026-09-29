#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    int size;
} Dict;

Dict* get_keys(char *dict[], int size) {
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
  
    d->keys = malloc(size * sizeof(char *));
    if (d->keys == NULL) {
        free(d);
        return NULL;
    }
  
    d->size = size;
    for(int i = 0; i < size; i++) {
        d->keys[i] = dict[i];
    }
    return d;
}

int main() {
    char *dict[] = {"key1", "key2", "key3", "key4"};
    int size = sizeof(dict) / sizeof(dict[0]);
    Dict *d = get_keys(dict, size);
    if (d == NULL) {
        return 1;
    }

    for(int i = 0; i < d->size; i++) {
        printf("%s\n", d->keys[i]);
    }

    free(d->keys);
    free(d);
    return 0;
}