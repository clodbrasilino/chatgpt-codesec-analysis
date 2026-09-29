#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_whitespaces(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, "[ \t\n\r]+", REG_EXTENDED);
    if (reti) {
        return;
    }

    regmatch_t pmatch[1];
    char *cursor = str;
    char *write_ptr = str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        size_t copy_len = match_start;
        memmove(write_ptr, cursor, copy_len);
        write_ptr += copy_len;

        cursor += match_end;
    }

    if (cursor != write_ptr) {
        size_t remaining_len = strlen(cursor);
        memmove(write_ptr, cursor, remaining_len);
        write_ptr += remaining_len;
        *write_ptr = '\0';
    }

    regfree(&regex);
}

int main(void) {
    char test_string[] = "  Hello \t World \n This is a test. \r  ";
    
    printf("Original: '%s'\n", test_string);
    remove_whitespaces(test_string);
    printf("Modified: '%s'\n", test_string);

    return 0;
}