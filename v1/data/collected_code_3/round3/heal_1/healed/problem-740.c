#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} dict;

dict* tuple_to_dict(char** tuple, int size) {
    dict* dictionary = (dict*)malloc(sizeof(dict) * (size / 2));
    if (dictionary == NULL)
        return NULL;

    for (int i = 0; i < size; i += 2) {
        dictionary[i / 2].key = tuple[i];
        dictionary[i / 2].value = tuple[i + 1];
    }
    return dictionary;
}

int main() {
    char* tuple[] = {"one", "1", "two", "2", "three", "3"};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    dict* dictionary = tuple_to_dict(tuple, size);
    if (dictionary == NULL)
        return 1;

    for (int i = 0; i < size / 2; i++) {
        printf("%s: %s\n", dictionary[i].key, dictionary[i].value);
    }

    free(dictionary);

    return 0;
}