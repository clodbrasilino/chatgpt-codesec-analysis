#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *pattern = "[a-z]+";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    char *cursor = str;
    char *write_ptr = str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_so;
        if (len > 0) {
            memmove(write_ptr, cursor, len);
            write_ptr += len;
        }
        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(cursor);
    if (remaining_len > 0) {
        memmove(write_ptr, cursor, remaining_len);
        write_ptr += remaining_len;
    }
    
    *write_ptr = '\0';

    regfree(&regex);
}

int main(void) {
    char test_str[] = "HELLO world THIS is A test STRING 123";
    
    remove_lowercase_substrings(test_str);
    
    printf("%s\n", test_str);
    
    return 0;
}