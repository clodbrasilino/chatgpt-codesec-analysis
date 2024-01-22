#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LENGTH 101
#define MAX_DICTIONARY_SIZE 1000

struct Dictionary {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[MAX_KEY_LENGTH];
    int value;
};

bool validKey(const char key[]) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    return key && strlen(key) < MAX_KEY_LENGTH;
}

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, const char key[]) {
    if(validKey(key)) {
        for (int i = 0; i < size && i < MAX_DICTIONARY_SIZE; i++) {
            if (strcmp(dict[i].key, key) == 0) {
                return dict[i].value;
            }
        }
    }
    return -1;  // Key not found
}

int main() {
    struct Dictionary dict[MAX_DICTIONARY_SIZE] = {{"key1", 1}, {"key2", 2}, {"key3", 3}};
    const char key[] = "key2";
    int value = accessDictionaryElementByKeyIndex(dict, 3, key);
    printf("Value: %d\n", value);
    return 0;
}