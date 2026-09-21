#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    regmatch_t pmatch[1];
    
    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    char *read_ptr = str;
    char *write_ptr = str;

    while (regexec(&regex, read_ptr, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        if (match_start > 0) {
            memmove(write_ptr, read_ptr, match_start);
            write_ptr += match_start;
        }

        read_ptr += match_end;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(read_ptr);
    if (remaining_len > 0) {
        memmove(write_ptr, read_ptr, remaining_len);
        write_ptr += remaining_len;
    }
    
    *write_ptr = '\0';

    regfree(&regex);
}

int main(void) {
    char str[] = "  Hello   \t World \n !  ";
    
    remove_whitespaces(str);
    
    printf("'%s'\n", str);
    
    return 0;
}