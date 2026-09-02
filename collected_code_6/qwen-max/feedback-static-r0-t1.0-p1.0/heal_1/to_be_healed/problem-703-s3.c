#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct {
    int key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
} Dictionary;

bool isKeyPresent(Dictionary *dict, int key) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->entries[i].key == key) {
            return true;
        }
    }
    return false;
}

int main() {
    Dictionary dict;
    dict.size = 3;
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    dict.entries = (DictionaryEntry *)malloc(dict.size * sizeof(DictionaryEntry));
    
    dict.entries[0].key = 1;
    dict.entries[0].value = "one";
    dict.entries[1].key = 2;
    dict.entries[1].value = "two";
    dict.entries[2].key = 3;
    dict.entries[2].value = "three";

    int keyToCheck = 2;
    if (isKeyPresent(&dict, keyToCheck)) {
        printf("Key %d is present in the dictionary.\n", keyToCheck);
    } else {
        printf("Key %d is not present in the dictionary.\n", keyToCheck);
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(dict.entries);
    return 0;
}