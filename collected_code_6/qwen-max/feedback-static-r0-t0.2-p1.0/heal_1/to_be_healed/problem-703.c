#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcmp'
  */

typedef struct {
    char *key;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::value' is never used. [unusedStructMember]
     */
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
} Dictionary;

bool isKeyPresent(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
         */
        if (dict->entries[i].key != NULL && key != NULL && strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    DictionaryEntry entries[] = {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"}
    };
    Dictionary dict = {entries, 3};

    const char *keyToFind = "two";
    if (isKeyPresent(&dict, keyToFind)) {
        printf("Key '%s' is present in the dictionary.\n", keyToFind);
    } else {
        printf("Key '%s' is not present in the dictionary.\n", keyToFind);
    }

    return 0;
}