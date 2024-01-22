#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 102
#define MAX_DICTIONARY_SIZE 1000

struct Dictionary {
    char key[MAX_KEY_LENGTH];
    int value;
};

bool validKey(const char *key) {
    if(key != NULL && (strnlen(key, MAX_KEY_LENGTH) < MAX_KEY_LENGTH)) {
        return true;
    }
    return false;
}

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, const char *key) {
    if(!validKey(key)) {
        return -1;
    }
    for (int i = 0; i < size && i < MAX_DICTIONARY_SIZE; i++) {
        if (strncmp(dict[i].key, key, MAX_KEY_LENGTH) == 0) {
            return dict[i].value;
        }
    }
    return -1;
}

int main() {
    struct Dictionary dict[MAX_DICTIONARY_SIZE] = {{"key1", 1}, {"key2", 2}, {"key3", 3}};
    const char key[] = "key2";
    int size = sizeof(dict) / sizeof(struct Dictionary);
    int value = accessDictionaryElementByKeyIndex(dict, size, key);
    printf("Value: %d\n", value);
    return 0;
}