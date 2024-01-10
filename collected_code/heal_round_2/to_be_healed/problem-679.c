#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_KEY_LENGTH 101

struct Dictionary {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[MAX_KEY_LENGTH];
    int value;
};

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, const char key[]) {
    assert(key != NULL);
    for (int i = 0; i < size; i++) {
        if (strncmp(dict[i].key, key, MAX_KEY_LENGTH - 1) == 0) {
            return dict[i].value;
        }
    }
    return -1;  // Key not found
}

int main() {
    struct Dictionary dict[3] = {{"key1", 1}, {"key2", 2}, {"key3", 3}};
    const char key[] = "key2";
    int value = accessDictionaryElementByKeyIndex(dict, 3, key);
    printf("Value: %d\n", value);
    return 0;
}