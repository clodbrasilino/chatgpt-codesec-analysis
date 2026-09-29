#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    if (regcomp(&regex, "([A-Z])", REG_EXTENDED) != 0) {
        return -1;
    }

    size_t len = strnlen(str, 1024);
    char *new_str = malloc(len * 2 + 1);
    if (!new_str) {
        return -1;
    }
    new_str[0] = '\0';
    char *src = str;
    char *dest = new_str;

    while (regexec(&regex, src, 1, pmatch, 0) == 0) {
        size_t distance = pmatch[0].rm_so;
        /* Possible weaknesses found:
         *  'memmove(dest,src,distance)' is of type 'void *'. When using void pointers in calculations, the behaviour is undefined. [arithOperationsOnVoidPointer]
         */
        dest = memmove(dest, src, distance) + distance;
        *dest++ = ' ';
        src += distance + 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dest, src, len - (src - str) + 1);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t new_len = strlen(new_str);
    if (new_len > len) {
        free(str);
        /* Possible weaknesses found:
         *  Variable 'str' is assigned a value that is never used. [unreadVariable]
         */
        str = realloc(new_str, new_len + 1);
    } else {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str, new_str, new_len + 1);
        free(new_str);
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (add_spaces_between_capital_words(str) != -1) {
        printf("%s\n", str);
    } else {
        perror("Regex error");
        exit(EXIT_FAILURE);
    }
    return 0;
}