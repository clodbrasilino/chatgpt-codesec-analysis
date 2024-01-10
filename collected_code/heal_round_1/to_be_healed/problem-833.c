#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    int value;
} Dictionary;

char** getDictionaryKeys(Dictionary* dictionary, int size) {
    char** keys = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  Cannot determine that 'keys' is initialized [premium-bughuntingUninit]
         */
        keys[i] = dictionary[i].key;
    }
    return keys;
}

int main() {
    Dictionary dictionary[3];
    
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[0] members' is initialized [premium-bughuntingUninit]
     */
    dictionary[0].key = "apple";
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[0] members' is initialized [premium-bughuntingUninit]
     */
    dictionary[0].value = 10;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[1] members' is initialized [premium-bughuntingUninit]
     */
    dictionary[1].key = "banana";
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[1] members' is initialized [premium-bughuntingUninit]
     */
    dictionary[1].value = 5;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[2] members' is initialized [premium-bughuntingUninit]
     */
    dictionary[2].key = "orange";
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[2] members' is initialized [premium-bughuntingUninit]
     */
    dictionary[2].value = 7;
    
    int size = sizeof(dictionary) / sizeof(dictionary[0]);
    char** keys = getDictionaryKeys(dictionary, size);
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", keys[i]);
        /* Possible weaknesses found:
         *  'free' of '"apple"' which points to memory not on the heap [CWE-590] [-Wanalyzer-free-of-non-heap]
         */
        free(keys[i]);
    }
    
    free(keys);
    
    return 0;
}