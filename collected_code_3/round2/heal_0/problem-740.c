#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

KeyValuePair* convertToDictionary(char *tuple[], int size) {
    KeyValuePair *dictionary = malloc(sizeof(KeyValuePair) * (size / 2));
    for(int i = 0; i < size; i += 2) {
        dictionary[i / 2].key = tuple[i];
        dictionary[i / 2].value = tuple[i + 1];
    }
    return dictionary;
}

int main() {
    char *tuple[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    KeyValuePair *dictionary = convertToDictionary(tuple, size);

    for(int i = 0; i < size / 2; i++) {
        printf("Key: %s, Value: %s\n", dictionary[i].key, dictionary[i].value);
    }

    free(dictionary);

    return 0;
}