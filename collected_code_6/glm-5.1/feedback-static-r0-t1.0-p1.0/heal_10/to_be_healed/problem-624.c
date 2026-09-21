#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *string_to_upper(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    char *upper_str = malloc(len + 1);
    if (upper_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\0') {
            upper_str[i] = '\0';
            return upper_str;
        }
        upper_str[i] = (char)toupper((unsigned char)str[i]);
    }
    upper_str[len] = '\0';

    return upper_str;
}

int main(void) {
    const char *original = "Hello, World! 123";
    size_t original_len = strnlen(original, 1024);
    
    char *converted = string_to_upper(original, original_len);

    if (converted != NULL) {
        printf("Original: %s\n", original);
        printf("Upper:    %s\n", converted);
        free(converted);
        converted = NULL;
    }

    /* Possible weaknesses found:
     *  Calling function 'string_to_upper' returns 0
     *  Variable 'null_result' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'null_result=string_to_upper(NULL,0)', assigned value is 0
     */
    char * const null_result = string_to_upper(NULL, 0);

    /* Possible weaknesses found:
     *  Condition 'null_result==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_result==NULL' is always true
     */
    if (null_result == NULL) {
        printf("Successfully handled NULL input.\n");
    }

    return 0;
}