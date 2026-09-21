#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces_regex(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    char *cursor = str;
    char *write_ptr = str;

    reti = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (reti != 0) {
        return;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_so;
        memmove(write_ptr, cursor, len);
        write_ptr += len;
        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(cursor);
    memmove(write_ptr, cursor, remaining_len);
    write_ptr[remaining_len] = '\0';

    regfree(&regex);
}

int main(void) {
    char str[] = "  Hello   World \t \n !  ";
    printf("Original: '%s'\n", str);
    remove_whitespaces_regex(str);
    printf("Modified: '%s'\n", str);
    return 0;
}