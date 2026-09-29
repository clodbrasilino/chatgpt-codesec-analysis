#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_characters(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[ ,.]+";
    const char replacement[] = ":";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *buffer = malloc(str_len + 1);
    if (!buffer) return;

    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        int len = 0;
        while (regexec(&regex, str + len, 1, pmatch, 0) == 0) {
            int match_start = pmatch[0].rm_so - len;
            int match_end = pmatch[0].rm_eo - len;
            for (int i = match_start; i < match_end; i++) {
                buffer[len + i] = replacement[0];
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(buffer + len + (match_end - match_start), str + len + match_end, strlen(str + len + match_end) + 1);
            len += match_end;
        }
        regfree(&regex);
        buffer[len] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(str, buffer);
    } else {
        /* Possible weaknesses found:
         *  Memory pointed to by 'buffer' is freed twice.
         */
        free(buffer);
    }
    /* Possible weaknesses found:
     *  Memory pointed to by 'buffer' is freed twice.
     *  Memory pointed to by 'buffer' is freed twice. [doubleFree]
     */
    free(buffer);
}

int main() {
    char input[] = "This is a test, to check. the function works properly with spaces, commas, and dots.";
    printf("Original: %s\n", input);
    replace_characters(input);
    printf("Modified: %s\n", input);
    return 0;
}