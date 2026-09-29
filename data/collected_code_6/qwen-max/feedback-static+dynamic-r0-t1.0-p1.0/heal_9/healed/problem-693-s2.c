#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void remove_multiple_spaces(char *input) {
    regex_t regex;
    regmatch_t matches[1];
    size_t input_len = strnlen(input, 4096);
    char *temp = malloc(input_len + 1);
    if (temp == NULL) {
        return;
    }
    snprintf(temp, input_len + 1, "%s", input);

    if (regcomp(&regex, "\\s{2,}", REG_NEWLINE | REG_EXTENDED) != 0) {
        free(temp);
        return;
    }

    int offset = 0;
    while (regexec(&regex, temp, 1, matches, 0) == 0) {
        memmove(temp + matches[0].rm_so - offset + 1, temp + matches[0].rm_eo - offset, strlen(temp + matches[0].rm_eo - offset) + 1);
        offset += matches[0].rm_eo - matches[0].rm_so - 1;
    }

    size_t new_len = input_len - offset;
    memcpy(input, temp, new_len);
    input[new_len] = '\0';
    free(temp);
    regfree(&regex);
}

int main() {
    char str[] = "This  is   a    test     string.";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}