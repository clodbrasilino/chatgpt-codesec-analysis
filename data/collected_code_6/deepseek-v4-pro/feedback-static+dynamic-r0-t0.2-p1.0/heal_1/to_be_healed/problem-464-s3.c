#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEY_LENGTH 64
#define MAX_DICT_SIZE 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
    int value;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    int size;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 1) {
        return true;
    }
    
    int first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strcpy(dict.entries[dict.size].key, "a");
    dict.entries[dict.size].value = 5;
    dict.size++;
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strcpy(dict.entries[dict.size].key, "b");
    dict.entries[dict.size].value = 5;
    dict.size++;
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strcpy(dict.entries[dict.size].key, "c");
    dict.entries[dict.size].value = 5;
    dict.size++;
    
    if (all_values_same(&dict)) {
        printf("All values are the same\n");
    } else {
        printf("Values are different\n");
    }
    
    dict.entries[2].value = 10;
    
    if (all_values_same(&dict)) {
        printf("All values are the same\n");
    } else {
        printf("Values are different\n");
    }
    
    return 0;
}