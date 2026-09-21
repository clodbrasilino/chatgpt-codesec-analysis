#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *input, size_t input_len) {
    const char pattern[] = "[[:space:]]+";
    regex_t reg;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[input_len + 1];
    regmatch_t match;
    int offset = 0;

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&reg, input + offset, 1, &match, 0) == 0) {
        if (match.rm_so == 0) {
            offset += 1;
            continue;
        }
        snprintf(result, sizeof(result), "%.*s %.*s", 
                 match.rm_so, input + offset, 
                 (int)(input_len - (offset + match.rm_eo)), input + offset + match.rm_eo);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t result_len = strlen(result);
        memmove(input + offset, result, result_len + 1);
        input_len -= (match.rm_eo - match.rm_so - 1);
        offset += 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "This  is   a    test string. ";
    size_t str_len = sizeof(str) - 1;
    remove_multiple_spaces(str, str_len);
    printf("%s\n", str);
    return 0;
}