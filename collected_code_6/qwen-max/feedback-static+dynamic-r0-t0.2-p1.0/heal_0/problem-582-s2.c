#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int size;
} Dictionary;

bool isDictionaryEmpty(const Dictionary *dict) {
    return dict->size == 0;
}

int main() {
    Dictionary myDict = {0};
    if (isDictionaryEmpty(&myDict)) {
        printf("The dictionary is empty.\n");
    } else {
        printf("The dictionary is not empty.\n");
    }
    return 0;
}