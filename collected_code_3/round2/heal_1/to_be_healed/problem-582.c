#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    int count;
} Dictionary;

int isDictionaryEmpty(Dictionary *dict) {
    return dict->count == 0;
}

int main() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->count = 0;

    if(isDictionaryEmpty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    free(dict);
    return 0;
}