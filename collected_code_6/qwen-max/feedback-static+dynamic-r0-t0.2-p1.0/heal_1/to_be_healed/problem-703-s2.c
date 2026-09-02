#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

bool isKeyPresent(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    Dictionary dict;
    dict.count = 3;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    dict.entries = (DictionaryEntry *)malloc(dict.count * sizeof(DictionaryEntry));

    dict.entries[0].key = "apple";
    dict.entries[0].value = "fruit";

    dict.entries[1].key = "carrot";
    dict.entries[1].value = "vegetable";

    dict.entries[2].key = "banana";
    dict.entries[2].value = "fruit";

    const char *keyToCheck = "carrot";
    if (isKeyPresent(&dict, keyToCheck)) {
        printf("Key '%s' is present in the dictionary.\n", keyToCheck);
    } else {
        printf("Key '%s' is not present in the dictionary.\n", keyToCheck);
    }

    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    free(dict.entries);
    return 0;
}