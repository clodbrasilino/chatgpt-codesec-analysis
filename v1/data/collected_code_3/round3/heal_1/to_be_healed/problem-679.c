#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} dict;

dict* create_dict(char* key, char* value) {
    dict* d = malloc(sizeof(dict));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'd' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    d->key = key;
    d->value = value;
    return d;
}

char* get_value_by_index(dict* d[], int index) {
    return d[index]->value;
}

int main() {
    dict* d[3];
    d[0] = create_dict("key1", "value1");
    d[1] = create_dict("key2", "value2");
    d[2] = create_dict("key3", "value3");

    printf("%s\n", get_value_by_index(d, 1));

    for(int i = 0; i < 3; i++) {
        free(d[i]);
    }

    return 0;
}