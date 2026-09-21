#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int replace_chars_with_colon(char *str) {
    regex_t reg;
    if (regcomp(&reg, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) return -1;

    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int pos = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *new_str = malloc(str_len * 2 + 1);
    if (!new_str) return -1;

    int new_pos = 0;
    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str + new_pos, str + pos, pmatch[0].rm_so - pos);
        new_pos += pmatch[0].rm_so - pos;
        new_str[new_pos++] = ':';
        pos += pmatch[0].rm_eo - pos;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str + new_pos, str + pos, str_len - pos + 1);

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    free(new_str);

    regfree(&reg);
    return 0;
}

int main() {
    char input[] = "Hello, world. This is a test, of the system.";
    if (replace_chars_with_colon(input) == 0) {
        printf("%s\n", input);
    } else {
        printf("Replacement failed.\n");
    }
    return 0;
}