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
    struct Dictionary *dict = (struct Dictionary *)malloc(sizeof(struct Dictionary));
    if (!dict) return NULL;
    
    dict->head = NULL;
    dict->count = 0;
    return dict;
}

void addKey(struct Dictionary *dict, char *key) {
    if (!dict) return;
    
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (!node) return;
    
    node->key = key;
    node->next = dict->head;
    dict->head = node;
    dict->count++;
}

char **getKeys(struct Dictionary *dict) {
    if (!dict) return NULL;

    char **keys = (char **)malloc(sizeof(char *) * dict->count);
    if (!keys) return NULL;

    struct Node *node = dict->head;
    for (int i = 0; i < dict->count; i++) {
        keys[i] = node->key;
        node = node->next;
    }
    return keys;
}

int main() {
    struct Dictionary *dict = createDictionary();
    if (!dict) return 1;

    addKey(dict, "key1");
    addKey(dict, "key2");
    addKey(dict, "key3");

    char **keys = getKeys(dict);
    if (!keys) {
        free(dict);
        return 1;
    }

    for (int i = 0; i < dict->count; i++) {
        printf("%s\n", keys[i]);
    }

    free(keys);
    free(dict);

    return 0;
}