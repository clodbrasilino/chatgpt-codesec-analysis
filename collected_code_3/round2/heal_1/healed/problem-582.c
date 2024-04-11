#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    int count;
} Dictionary;

int isDictionaryEmpty(Dictionary *dict) {
    if (dict != NULL) {
        return dict->count == 0;
    }
    return 1;
}

int main() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if(dict == NULL) {
        printf("Failed to allocate memory for dictionary\n");
        return 1; //Return non-zero code to indicate failure
    }
    dict->count = 0;

    if(isDictionaryEmpty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    free(dict);
    return 0;
}