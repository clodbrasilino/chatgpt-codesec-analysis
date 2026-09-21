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
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (len >= sizeof(buffer)) return -1;
        snprintf(buffer, sizeof(buffer), "%.*s:", (int)pmatch[0].rm_eo, str + pos);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + pos + 1, str + pos + len, strlen(str + pos + len) + 1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memcpy(str + pos, buffer, strlen(buffer));
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        pos += strlen(buffer);
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