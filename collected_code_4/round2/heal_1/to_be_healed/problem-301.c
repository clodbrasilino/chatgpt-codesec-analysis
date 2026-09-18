#include <stdlib.h>
#include <string.h>

typedef struct Dict {
    char *key;
    char *value;
    struct Dict *child;
} Dict;

int depthOfDictionary(Dict *dict) {
    int depth = 0, maxDepth = 0;

    Dict *temp = dict;
    while (temp) {
        int depth = depthOfDictionary(temp->child);
        if (depth > maxDepth)
            maxDepth = depth;
        temp = temp->child;
    }

    return maxDepth + 1;
}

int main() {
    Dict *dict = malloc(sizeof(Dict));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->key = strdup("key1");
    dict->value = strdup("value1");

    dict->child = malloc(sizeof(Dict));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*dict.child' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->child->key = strdup("key2");
    dict->child->value = strdup("value2");
    dict->child->child = NULL;

    int depth = depthOfDictionary(dict);

    free(dict->child->key);
    free(dict->child->value);
    free(dict->child);

    free(dict->key);
    free(dict->value);
    free(dict);

    return 0;
}