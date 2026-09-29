#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int count;
} Dictionary;

bool dictionary_is_empty(const Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->count == 0;
}

int main(void) {
    Dictionary dict = { .count = 0 };

    if (dictionary_is_empty(&dict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    return 0;
}