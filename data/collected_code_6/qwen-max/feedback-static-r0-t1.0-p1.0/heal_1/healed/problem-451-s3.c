#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_whitespace(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    int ret;

    if (regcomp(&regex, "\\s", REG_EXTENDED|REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while ((ret = regexec(&regex, input, 1, &match, 0)) == 0) {
        size_t len = strlen(input + match.rm_eo);
        memmove(input + match.rm_so, input + match.rm_eo, len + 1);
        input = input + match.rm_so;
    }

    if (ret != REG_NOMATCH) {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        return;
    }

    snprintf(output, output_size, "%s", input);
    regfree(&regex);
}

int main() {
    const char *input = " This is a test string with  spaces. ";
    char output[50];

    remove_whitespace(input, output, sizeof(output));
    printf("Result: '%s'\n", output);

    return 0;
}