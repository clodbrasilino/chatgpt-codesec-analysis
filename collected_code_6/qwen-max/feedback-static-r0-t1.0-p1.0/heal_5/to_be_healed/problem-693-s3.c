#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *input) {
    static const char pattern[] = "[[:space:]]+";
    regex_t reg;
    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE)) {
        return;
    }

    regmatch_t match;
    int offset = 0;

    while (regexec(&reg, input + offset, 1, &match, 0) == 0) {
        if (match.rm_so == 0) {
            offset += 1;
            continue;
        }
        size_t len_before = match.rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len_after = match.rm_eo - match.rm_so + strlen(input + offset + match.rm_eo);
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (len_before + len_after + 1 < 1024 && strlen(input) < 1024) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char result[1024];
            snprintf(result, 1024, "%.*s %.*s", 
                     (int)len_before, input + offset, 
                     /* Possible weaknesses found:
                      * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                      */
                     (int)(strlen(input + offset + match.rm_eo)), input + offset + match.rm_eo);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(result) < 1024) {
                memmove(input + offset + len_before + 1, input + offset + match.rm_eo, len_after + 1);
                input[offset + len_before] = ' ';
                offset += 1;
            }
        }
    }

    regfree(&reg);
}

int main() {
    char str[] = "This  is   a    test string. ";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}