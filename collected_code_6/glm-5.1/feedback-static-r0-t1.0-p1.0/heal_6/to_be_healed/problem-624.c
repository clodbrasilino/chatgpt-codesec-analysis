#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *string_to_upper(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    char *upper_str = malloc(len + 1);
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
     *  Condition 'string_to_upper(NULL)==NULL' is always true
     *  Condition 'string_to_upper(NULL)==NULL' is always true [knownConditionTrueFalse]
     *  Calling function 'string_to_upper' returns 0
     */
    if (string_to_upper(NULL) == NULL) {
        printf("Successfully handled NULL input.\n");
    }

    return 0;
}