#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void insert_spaces(char *str) {
    regex_t reg;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    size_t str_len = strlen(str);
    char *new_str = malloc((str_len * 2 + 1) * sizeof(char));
    if (!new_str) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_str[0] = '\0';
    char *result = new_str;

    while (regexec(&reg, str, 1, match, 0) == 0) {
        size_t n = match[0].rm_eo - match[0].rm_so;
        strncat(result, str + match[0].rm_so, n);
        result += n;
        *result++ = ' ';
        str += n;
    }
    strncat(result, str, str_len);

    strncpy(str, new_str, str_len * 2 + 1);
    str[str_len * 2] = '\0';
    free(new_str);
    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    insert_spaces(str);
    printf("%s\n", str);
    return 0;
}