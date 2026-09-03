#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_before_caps(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    size_t str_len = strlen(str);
    char *new_str = malloc((str_len * 2 + 1) * sizeof(char));
    int new_str_index = 0;

    if (regcomp(&regex, "([A-Z])", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression\n");
        exit(1);
    }

    for (char *p = str; *p; ++p) {
        if (regexec(&regex, p, 1, pmatch, 0) == 0 && pmatch[0].rm_so == 0) {
            if (new_str_index > 0 && new_str[new_str_index-1] != ' ')
                new_str[new_str_index++] = ' ';
            new_str[new_str_index++] = *p;
        } else {
            new_str[new_str_index++] = *p;
        }
    }
    new_str[new_str_index] = '\0';

    strncpy(str, new_str, str_len * 2 + 1);
    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "ThisIsASampleString";
    add_spaces_before_caps(str);
    printf("%s\n", str);
    return 0;
}