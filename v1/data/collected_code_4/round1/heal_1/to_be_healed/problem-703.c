#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

int keyInDictionary(Dictionary* dictionary, const char* key) {
    if(dictionary == NULL || key == NULL)
        return 0;
    
    for(size_t i = 0; i < dictionary->size; ++i)
        if(strcmp(dictionary->pairs[i].key, key) == 0)
            return 1;
    
    return 0;
}

int main() {
    KeyValuePair pairs[] = {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"},
    };
    Dictionary dictionary = {pairs, sizeof(pairs) / sizeof(pairs[0])};

    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     */
    printf("Key2 is in dictionary: %s\n", keyInDictionary(&dictionary, "key2") ? "Yes" : "No");
    printf("Key4 is in dictionary: %s\n", keyInDictionary(&dictionary, "key4") ? "Yes" : "No");

    return 0;
}