#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_characters(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[ ,.]+";
    /* Possible weaknesses found:
     *  Variable 'replacement' can be declared as const array [constVariable]
     */
    char replacement[] = ":";
    /* Possible weaknesses found:
     *  The scope of the variable 'buffer' can be reduced. [variableScope]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        if (regexec(&regex, str, 1, pmatch, 0) != REG_NOMATCH) {
            regfree(&regex);
            int len = 0;
            /* Possible weaknesses found:
             *  The scope of the variable 'pm' can be reduced. [variableScope]
             */
            regmatch_t *pm;

            while (1) {
                pm = pmatch;
                for (int i = 0; i <= pm[0].rm_eo - pm[0].rm_so; i++) {
                    buffer[len + i] = replacement[0];
                }
                len += (pm[0].rm_eo - pm[0].rm_so);
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                memmove(str + pm[0].rm_eo, str + pm[0].rm_so, strlen(str) + 1 - (pm[0].rm_so + (pm[0].rm_eo - pm[0].rm_so)));
                len += pm[0].rm_so;
                regexec(&regex, str + len, 1, pmatch, 0);
                if (pmatch[0].rm_so == -1) break;
                buffer[len] = '\0';
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
                 */
                strcat(str, buffer + len);
                memset(buffer, 0, 1024);
            }
        }
        regfree(&regex);
    }
}

int main() {
    char input[] = "This is a test, to check. the function works properly with spaces, commas, and dots.";
    printf("Original: %s\n", input);
    replace_characters(input);
    printf("Modified: %s\n", input);
    return 0;
}