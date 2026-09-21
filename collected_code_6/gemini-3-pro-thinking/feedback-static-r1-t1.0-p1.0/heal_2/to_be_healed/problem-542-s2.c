#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_with_colon(char *str) {
    regex_t regex;
    int comp_res;
    int exec_res;
    regmatch_t pmatch[1];
    char *cursor;

    if (str == NULL) {
        return -1;
    }

    comp_res = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (comp_res != 0) {
        return -1;
    }

    cursor = str;
    while ((exec_res = regexec(&regex, cursor, 1, pmatch, 0)) == 0) {
        cursor[pmatch[0].rm_so] = ':';
        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);

    if (exec_res != REG_NOMATCH) {
        return -1;
    }

    return 0;
}

int main(void) {
    const char *original = "This is a test, with spaces. commas, and dots.";
    size_t len;
    char *str;
    int res;

    len = strnlen(original, 256);
    str = (char *)malloc(len + 1);
    if (str == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, original, len);
    str[len] = '\0';

    res = replace_with_colon(str);
    if (res == 0) {
        printf("%s\n", str);
    }

    free(str);

    return (res == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}