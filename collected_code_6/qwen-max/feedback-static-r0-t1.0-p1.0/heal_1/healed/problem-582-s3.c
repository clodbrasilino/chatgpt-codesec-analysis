#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int keys;
} Dictionary;

bool is_dictionary_empty(const Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->keys == 0;
}

int main() {
    Dictionary my_dict = {0};
    if (is_dictionary_empty(&my_dict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }
    return 0;
}