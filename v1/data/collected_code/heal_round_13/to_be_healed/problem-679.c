#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 102
#define MAX_DICTIONARY_SIZE 1000

struct Dictionary {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[MAX_KEY_LENGTH];
    int value;
};

bool validKey(const char *key) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(key != NULL && (strlen(key) < MAX_KEY_LENGTH-1)) {
        return true;
    }
    return false;
}

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, const char *key) {
    if(!validKey(key)) {
        return -1;
    }
    for (int i = 0; i < size && i < MAX_DICTIONARY_SIZE; i++) {
        if (strncmp(dict[i].key, key, MAX_KEY_LENGTH-1) == 0) {
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