#include <stdio.h>
#include <stdlib.h>

struct Node {
    char *key;
    struct Node *next;
};

struct Dictionary {
    struct Node *head;
    int count;
};

struct Dictionary *createDictionary() {
    struct Dictionary *dict = malloc(sizeof(struct Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->head = NULL;
    dict->count = 0;
    return dict;
}

void addKey(struct Dictionary *dict, char *key) {
    struct Node *node = malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->key = key;
    node->next = dict->head;
    dict->head = node;
    dict->count++;
}

char **getKeys(struct Dictionary *dict) {
    char **keys = malloc(sizeof(char *) * dict->count);
    struct Node *node = dict->head;
    for (int i = 0; i < dict->count; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        keys[i] = node->key;
        node = node->next;
    }
    return keys;
}

int main() {
    struct Dictionary *dict = createDictionary();
    addKey(dict, "key1");
    addKey(dict, "key2");
    addKey(dict, "key3");

    char **keys = getKeys(dict);
    for (int i = 0; i < dict->count; i++) {
        printf("%s\n", keys[i]);
    }

    free(keys);
    free(dict);

    return 0;
}