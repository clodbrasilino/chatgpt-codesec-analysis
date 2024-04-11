#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int size;
} Dictionary;

int checkKey(Dictionary *dict, char *key) {
    for(int i = 0; i < dict->size; i++) {
        if(strcmp(dict->pairs[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Dictionary dict;
    dict.size = 3;
    dict.pairs = malloc(sizeof(KeyValuePair) * dict.size);

    strcpy(dict.pairs[0].key, "key1");
    strcpy(dict.pairs[0].value, "value1");

    strcpy(dict.pairs[1].key, "key2");
    strcpy(dict.pairs[1].value, "value2");

    strcpy(dict.pairs[2].key, "key3");
    strcpy(dict.pairs[2].value, "value3");

    char keyToCheck[50];
    printf("Enter a key to check: ");
    scanf("%s", keyToCheck);

    if(checkKey(&dict, keyToCheck)) {
        printf("Key is present in the dictionary.\n");
    } else {
        printf("Key is not present in the dictionary.\n");
    }

    free(dict.pairs);
    return 0;
}