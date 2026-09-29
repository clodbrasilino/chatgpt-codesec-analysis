#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

bool are_all_dictionaries_empty(Dictionary* dict_list, size_t num_dicts) {
    if (dict_list == NULL && num_dicts > 0) {
        return false;
    }

    for (size_t i = 0; i < num_dicts; i++) {
        if (dict_list[i].size > 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    Dictionary dicts[3];
    
    for (int i = 0; i < 3; i++) {
        dicts[i].pairs = NULL;
        dicts[i].size = 0;
    }

    bool result1 = are_all_dictionaries_empty(dicts, 3);
    printf("%d\n", result1);

    dicts[1].size = 1;
    KeyValuePair pair = {1, 100};
    dicts[1].pairs = &pair;

    printf("%d %d\n", dicts[1].pairs[0].key, dicts[1].pairs[0].value);

    bool result2 = are_all_dictionaries_empty(dicts, 3);
    printf("%d\n", result2);

    return 0;
}