#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *add_spaces_capitals(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    char *result = malloc(len * 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_idx = 0;

    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i]) && i > 0 && str[i - 1] != ' ') {
            result[dst_idx++] = ' ';
        }
        result[dst_idx++] = str[i];
    }

    result[dst_idx] = '\0';
    return result;
}

int main(void) {
    const char *tests[] = {
        "HelloWorld",
        "ThisIsATest",
        "Already Spaced",
        "NoSpacesHere",
        "ABC",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tests[i]);
        char *res = add_spaces_capitals(tests[i], len);
        if (res != NULL) {
            printf("Input: %s\nOutput: %s\n\n", tests[i], res);
            free(res);
        }
    }

    return 0;
}