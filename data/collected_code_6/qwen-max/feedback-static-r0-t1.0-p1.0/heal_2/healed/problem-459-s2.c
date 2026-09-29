#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    int reti;
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
    strcpy(new_str, str);

    while (1) {
        reti = regexec(&regex, new_str, 3, (regmatch_t *)malloc(sizeof(regmatch_t) * 3), 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            free(new_str);
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
        size_t match_start, match_end;
        match_start = ((regmatch_t *)malloc(sizeof(regmatch_t) * 3))[0].rm_so;
        match_end = ((regmatch_t *)malloc(sizeof(regmatch_t) * 3))[0].rm_eo;
        memmove(new_str + match_start, new_str + match_end, len - match_end + 1);
        len -= (match_end - match_start);
    }

    free(new_str);
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