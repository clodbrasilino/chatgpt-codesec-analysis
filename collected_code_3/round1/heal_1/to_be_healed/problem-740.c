#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

KeyValuePair* convertToDictionary(char** tuple, int size) {
    KeyValuePair* dictionary = malloc((size / 2) * sizeof(KeyValuePair));
    for (int i = 0; i < size; i += 2) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'dictionary' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        dictionary[i / 2].key = tuple[i];
        dictionary[i / 2].value = tuple[i + 1];
    }
    return dictionary;
}

int main() {
    char* tuple[] = {"one", "1", "two", "2", "three", "3"};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    KeyValuePair* dictionary = convertToDictionary(tuple, size);

    for (int i = 0; i < size / 2; i++) {
        printf("%s: %s\n", dictionary[i].key, dictionary[i].value);
    }

    free(dictionary);

    return 0;
}