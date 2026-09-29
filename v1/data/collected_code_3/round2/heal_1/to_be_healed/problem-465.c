#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Item;

void drop_empty_items(Item *items, int *size) {
    int i, j = 0;
    for(i = 0; i < *size; i++) {
        if(items[i].key != NULL && items[i].value != NULL) {
            items[j++] = items[i];
        }
    }
    *size = j;
}

int main() {
    int size = 5;
    Item *items = malloc(size * sizeof(Item));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'items' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    items[0].key = "key1"; items[0].value = "value1";
    items[1].key = NULL; items[1].value = "value2";
    items[2].key = "key3"; items[2].value = NULL;
    items[3].key = NULL; items[3].value = NULL;
    items[4].key = "key5"; items[4].value = "value5";

    drop_empty_items(items, &size);

    int i;
    for(i = 0; i < size; i++) {
        printf("%s: %s\n", items[i].key, items[i].value);
    }

    free(items);
    return 0;
}