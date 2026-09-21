#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t write_pos = 0;
    for (size_t i = 0; i < length; i++) {
        if (!isspace((unsigned char)str[i])) {
            result[write_pos++] = str[i];
        }
    }

    result[write_pos] = '\0';

    char *shrunk = realloc(result, write_pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "Google Flutter",
        "Google Dart",
        "iOS Swift",
        "  H e l l o \t W o r l d \n "
    };
    
    setbuf(stdout, NULL);

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        char *result = remove_whitespaces(tests[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    return 0;
}