#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_before_caps(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) return;
    
    char *new_str = malloc((len * 2 + 1) * sizeof(char));
    if (!new_str) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    int new_str_index = 0;
    
    if (regcomp(&regex, "([A-Z])", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression\n");
        exit(1);
    }

    for (char *p = str; *p; ++p) {
        if (regexec(&regex, p, 1, pmatch, 0) == 0 && pmatch[0].rm_so == 0) {
            if (new_str_index > 0 && new_str[new_str_index-1] != ' ') {
                new_str[new_str_index++] = ' ';
            }
            new_str[new_str_index++] = *p;
        } else {
            new_str[new_str_index++] = *p;
        }
    }
    new_str[new_str_index] = '\0';

    regfree(&regex);
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, len * 2 + 1);
    free(new_str);
}

int main() {
    char str[] = "ThisIsASampleString";
    add_spaces_before_caps(str);
    printf("%s\n", str);
    return 0;
}