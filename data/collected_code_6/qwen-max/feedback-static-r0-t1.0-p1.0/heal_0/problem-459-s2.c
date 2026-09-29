#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    
    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        size_t len = strlen(str);
        char *new_str = (char *)malloc(len + 1);
        if (new_str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        
        while (reti == 0) {
            reti = regexec(&regex, str, 0, NULL, 0);
            if (reti == 0) {
                size_t match_start, match_end;
                regoff_t ovector[6];
                reti = regexec(&regex, str, 3, ovector, 0);
                if (reti == 0) {
                    match_start = ovector[0];
                    match_end = ovector[1];
                    memmove(str + match_start, str + match_end, len - match_end + 1);
                    len -= (match_end - match_start);
                }
            }
        }
        
        strcpy(new_str, str);
        free(new_str);
    } else if (reti == REG_NOMATCH) {
        // No uppercase substrings found
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    
    regfree(&regex);
}

int main() {
    char str[] = "aBcDeFgHiJkLmNoP";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}