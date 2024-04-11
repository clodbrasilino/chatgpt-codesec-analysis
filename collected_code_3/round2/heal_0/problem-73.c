#include <stdio.h>
#include <string.h>
#include <regex.h>

void split_string(char *str, char *regex_pattern) {
    char *p = str;
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
        printf("Failed to compile regex.\n");
        return;
    }

    while (1) {
        if (regexec(&regex, p, 1, &match, 0) == 0) {
            if (match.rm_so != 0) {
                printf("%.*s\n", (int)match.rm_so, p);
            }
            p += match.rm_eo;
        } else {
            printf("%s\n", p);
            break;
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, how are you? I am fine.";
    char regex_pattern[] = "[ ,.?!]+";
    split_string(str, regex_pattern);
    return 0;
}