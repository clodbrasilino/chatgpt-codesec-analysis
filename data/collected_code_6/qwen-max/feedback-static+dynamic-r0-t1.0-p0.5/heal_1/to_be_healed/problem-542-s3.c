#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'rc' can be reduced. [variableScope]
     */
    int rc, i = 0;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return;
    }

    while (1) {
        rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH) break;
        if (rc != 0) {
            regfree(&regex);
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(buffer, str + i, pmatch[0].rm_eo - pmatch[0].rm_so);
        buffer[pmatch[0].rm_eo - pmatch[0].rm_so] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + i + 1, str + i + (pmatch[0].rm_eo - pmatch[0].rm_so), strlen(str + i + (pmatch[0].rm_eo - pmatch[0].rm_so)) + 1);
        str[i] = ':';
        i += 1;
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}