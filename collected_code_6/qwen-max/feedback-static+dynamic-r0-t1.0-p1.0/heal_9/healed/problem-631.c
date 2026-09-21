#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void swap_whitespace_underscore(char *str, size_t len) {
    regex_t re;
    regmatch_t match;

    if (regcomp(&re, " ", REG_EXTENDED)) return;

    char *new_str = (char *)malloc(len + 1);
    if (!new_str) return;
    memcpy(new_str, str, len);
    new_str[len] = '\0';

    while (regexec(&re, new_str, 1, &match, 0) == 0) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = '_';
        len++;
        new_str[len] = '\0';
    }
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED)) return;
    while (regexec(&re, new_str, 1, &match, 0) == 0) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = ' ';
        len++;
        new_str[len] = '\0';
    }
    regfree(&re);

    snprintf(str, len + 1, "%s", new_str);
    free(new_str);
}

int main() {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_len;

    if ((read_len = getline(&input, &input_size, stdin)) != -1) {
        input[strcspn(input, "\n")] = 0;
        size_t len = strlen(input);
        if (len > 0) {
            swap_whitespace_underscore(input, len);
            printf("%s\n", input);
        }
        free(input);
    }
    return 0;
}