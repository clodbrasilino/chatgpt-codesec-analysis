#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void sanitize_string(char *input) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "[^a-zA-Z0-9]";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, input, 1, match, 0) == 0) {
        size_t len = strlen(input);
        memmove(input + match[0].rm_so, input + match[0].rm_eo, len - match[0].rm_eo + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_string(input);
    printf("%s\n", input);
    return 0;
}