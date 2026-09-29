#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Dictionary::keys' is never used. [unusedStructMember]
     */
    char **keys;
    /* Possible weaknesses found:
     *  struct member 'Dictionary::values' is never used. [unusedStructMember]
     */
    char **values;
    size_t count;
} Dictionary;

bool all_dictionaries_empty(const Dictionary *dictionaries, size_t count) {
    if (count == 0) {
        return true;
    }
    if (dictionaries == NULL) {
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        if (dictionaries[i].count != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dictionaries[3] = { {0} };

    printf("%s\n", all_dictionaries_empty(dictionaries, 3) ? "true" : "false");

    dictionaries[1].count = 1;
    printf("%s\n", all_dictionaries_empty(dictionaries, 3) ? "true" : "false");

    /* Possible weaknesses found:
     *  Condition 'all_dictionaries_empty(NULL,0)' is always true [knownConditionTrueFalse]
     *  Calling function 'all_dictionaries_empty' returns 1
     *  Condition 'all_dictionaries_empty(NULL,0)' is always true
     */
    printf("%s\n", all_dictionaries_empty(NULL, 0) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'all_dictionaries_empty(NULL,1)' is always false [knownConditionTrueFalse]
     *  Calling function 'all_dictionaries_empty' returns 0
     *  Condition 'all_dictionaries_empty(NULL,1)' is always false
     */
    printf("%s\n", all_dictionaries_empty(NULL, 1) ? "true" : "false");

    return 0;
}