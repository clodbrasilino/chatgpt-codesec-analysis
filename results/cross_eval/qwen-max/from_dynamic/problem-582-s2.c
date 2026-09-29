#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->count = 0;
    return dict;
}

void freeDictionary(Dictionary* dict) {
    free(dict);
}

bool isDictionaryEmpty(const Dictionary* dict) {
    return (dict != NULL && dict->count == 0);
}

int main() {
    Dictionary* myDict = createDictionary();
    if (myDict == NULL) {
        fprintf(stderr, "Failed to allocate memory for dictionary\n");
        return 1;
    }

    printf("Is dictionary empty? %s\n", isDictionaryEmpty(myDict) ? "Yes" : "No");

    freeDictionary(myDict);
    return 0;
}