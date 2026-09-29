#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    char msgbuf[100];

    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    size_t len = strlen(str);
    char *new_str = malloc(len + 1);
    if (new_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    snprintf(new_str, len + 1, "%s", str);

    while (1) {
        regmatch_t matches[3];
        int reti = regexec(&regex, new_str, 3, matches, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            free(new_str);
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        memmove(new_str + match_start, new_str + match_end, len - match_end + 1);
        len -= (match_end - match_start);
    }

    new_str = realloc(new_str, len + 1);
    if (new_str == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(1);
    }
    strncpy(str, new_str, len);
    str[len] = '\0';
    free(new_str);

    regfree(&regex);
}

int main() {
    char str[] = "aBcDeFgHiJkLmNoP";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}