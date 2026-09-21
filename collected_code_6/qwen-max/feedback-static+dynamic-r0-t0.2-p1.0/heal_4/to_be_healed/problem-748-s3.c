#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void insert_spaces(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *new_str = malloc(str_len * 2 + 1);
    if (!new_str) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    size_t new_pos = 0;
    char *curr_pos = str;

    while (regexec(&regex, curr_pos, 1, match, 0) == 0) {
        size_t match_start = match[0].rm_so;
        size_t match_end = match[0].rm_eo;
        memmove(new_str + new_pos, curr_pos, match_start);
        new_pos += match_start;
        
        if (new_pos > 0 && (new_pos - 1 < str_len && new_str[new_pos - 1] != ' ')) {
            new_str[new_pos++] = ' ';
        }

        memmove(new_str + new_pos, curr_pos + match_start, match_end - match_start);
        new_pos += match_end - match_start;
        
        if (new_pos > 0 && (new_pos - 1 < str_len && new_str[new_pos - 1] != ' ')) {
            new_str[new_pos++] = ' ';
        }

        curr_pos += match_end;
        if (curr_pos >= str + str_len) break;
    }

    if (curr_pos < str + str_len) {
        memmove(new_str + new_pos, curr_pos, str_len - (curr_pos - str));
        new_pos += (str_len - (curr_pos - str));
    }

    new_str[new_pos] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, str_len * 2 + 1);
    free(new_str);
    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    insert_spaces(input);
    printf("%s\n", input);
    return 0;
}