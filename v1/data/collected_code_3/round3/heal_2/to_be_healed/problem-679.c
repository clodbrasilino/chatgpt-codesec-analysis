#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} dict;

dict* create_dict(char* key, char* value) {
    dict* d = (dict*)malloc(sizeof(dict));
    if(d == NULL) {
        return NULL;
    }

    d->key = strdup(key);
    d->value = strdup(value);

    return d;
}

char* get_value_by_index(dict* d[], int index) {
    if(d[index]) {
        return d[index]->value;
    } else {
        return NULL;
    }
}

int main() {
    dict* d[3];
    d[0] = create_dict("key1", "value1");
    if(d[0] == NULL) return 1;
    d[1] = create_dict("key2", "value2");
    if(d[1] == NULL) return 1;
    d[2] = create_dict("key3", "value3");
    if(d[2] == NULL) return 1;

    /* Possible weaknesses found:
     *  use of possibly-NULL 'get_value_by_index(&d, 1)' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
     */
    printf("%s\n", get_value_by_index(d, 1));

    for(int i = 0; i < 3; i++) {
        free(d[i]->key);
        free(d[i]->value);
        free(d[i]);
    }

    return 0;
}