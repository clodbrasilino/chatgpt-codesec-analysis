#include <stdio.h>
#include <regex.h>
#include <string.h>

int replace_chars_with_colon(char *str) {
    regex_t reg;
    if (regcomp(&reg, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) return -1;

    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int pos = 0;
    /* Possible weaknesses found:
     *  Variable 'original_str' is assigned a value that is never used. [unreadVariable]
     */
    char *original_str = str;

    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[len + 2];
        snprintf(buffer, sizeof(buffer), "%.*s:", (int)len, str + pos + pmatch[0].rm_so);

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + pos + len + 1, str + pos + pmatch[0].rm_eo, strlen(str + pos + pmatch[0].rm_eo) + 1);
        memmove(str + pos, buffer, len + 1);
        pos += len + 1;
    }

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