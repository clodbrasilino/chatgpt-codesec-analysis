#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *string_to_upper(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *upper_str = (char *)malloc(len + 1);
    if (upper_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        upper_str[i] = (char)toupper((unsigned char)str[i]);
    }
    upper_str[len] = '\0';

    return upper_str;
}

int main(void) {
    const char *original = "Hello, World! 123";
    char *converted = string_to_upper(original);

    if (converted != NULL) {
        printf("Original: %s\n", original);
        printf("Upper:    %s\n", converted);
        free(converted);
        converted = NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=string_to_upper(NULL)', assigned value is 0
     *  Calling function 'string_to_upper' returns 0
     */
    char *null_test = string_to_upper(NULL);

    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("NULL input handled successfully.\n");
    } else {
        free(null_test);
        null_test = NULL;
    }

    return 0;
}