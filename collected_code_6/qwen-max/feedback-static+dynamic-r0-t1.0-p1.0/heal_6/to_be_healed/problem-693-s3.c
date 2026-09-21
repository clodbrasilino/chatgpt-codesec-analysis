#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *input) {
    static const char pattern[] = "[[:space:]]+";
    regex_t reg;
    size_t input_len = strnlen(input, 1024);
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
        snprintf(result, input_len - offset + 1, "%.*s %s", 
                 match.rm_so, input + offset, 
                 input + offset + match.rm_eo);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(input + offset, result, input_len - offset);
        input[input_len] = '\0';
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