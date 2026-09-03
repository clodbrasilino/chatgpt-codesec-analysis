#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int size;
} Dictionary;

bool are_all_dictionaries_empty(Dictionary **dicts, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (dicts[i]->size != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    size_t count = 3;
    Dictionary *dict1 = (Dictionary *)malloc(sizeof(Dictionary));
    dict1->size = 0;
    Dictionary *dict2 = (Dictionary *)malloc(sizeof(Dictionary));
    dict2->size = 0;
    Dictionary *dict3 = (Dictionary *)malloc(sizeof(Dictionary));
    dict3->size = 0;

    Dictionary *dicts[] = {dict1, dict2, dict3};

    bool result = are_all_dictionaries_empty(dicts, count);
    free(dict1);
    free(dict2);
    free(dict3);

    return 0;
}