#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *input) {
    static const char pattern[] = "[[:space:]]+";
    regex_t reg;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[1024];
    regmatch_t match;
    /* Possible weaknesses found:
     *  Unused variable: reti [unusedVariable]
     */
    int offset = 0, reti;

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&reg, input + offset, 1, &match, 0) == 0) {
        if (match.rm_so == 0) {
            offset += 1;
            continue;
        }
        snprintf(result, 1024, "%.*s %.*s", 
                 match.rm_so, input + offset, 
                 /* Possible weaknesses found:
                  * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                  */
                 (int)(strlen(input + offset) - match.rm_eo), 
                 input + offset + match.rm_eo);
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(input + offset, result);
        offset += 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "This  is   a    test string. ";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}