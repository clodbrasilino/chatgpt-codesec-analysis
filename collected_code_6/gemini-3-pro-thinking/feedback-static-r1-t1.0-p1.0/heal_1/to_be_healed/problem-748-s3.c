#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *insert_spaces(const char *input) {
    regex_t regex;
    int ret;
    size_t len;
    char *result;
    const char *cursor;
    char *out;
    regmatch_t pmatch[1];

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > ((size_t)-1 / 2) - 1) {
        regfree(&regex);
        return NULL;
    }

    result = (char *)malloc(len * 2 + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    out = result;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t offset = (size_t)pmatch[0].rm_so;

        if (offset > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(out, cursor, offset);
            out += offset;
        }

        if ((cursor + offset) > input) {
            if (*(cursor + offset - 1) != ' ') {
                *out = ' ';
                out++;
            }
        }

        *out = cursor[offset];
        out++;
        cursor += offset + 1;

        if (*cursor == '\0') {
            break;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out, cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_str = "HelloWorldThisIsATest";
    char *spaced_str;

    spaced_str = insert_spaces(test_str);
    if (spaced_str != NULL) {
        printf("%s\n", spaced_str);
        free(spaced_str);
    }

    return 0;
}