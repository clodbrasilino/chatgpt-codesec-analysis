#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_KEY_LENGTH 101
#define MAX_DICTIONARY_SIZE 1000

struct Dictionary {
    char key[MAX_KEY_LENGTH];
    int value;
};

bool validKey(const char key[]) {
    return key && strnlen(key, MAX_KEY_LENGTH) < MAX_KEY_LENGTH;
}

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, const char key[]) {
    if(validKey(key)) {
        for (int i = 0; i < size; i++) {
            if (strncmp(dict[i].key, key, MAX_KEY_LENGTH) == 0) {
                return dict[i].value;
            }
        }
    }
    return -1;  // Key not found
}

int main() {
    assert(MAX_DICTIONARY_SIZE >=3);
    struct Dictionary dict[MAX_DICTIONARY_SIZE] = {{"key1", 1}, {"key2", 2}, {"key3", 3}};
    const char key[] = "key2";
    int value = accessDictionaryElementByKeyIndex(dict, 3, key);
    printf("Value: %d\n", value);
    return 0;
}