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

    const char *p = input;
    size_t len = 0;

    while ((ret = regexec(&regex, p, 1, &match, 0)) == 0) {
        if (len + (match.rm_so - (p - input)) >= output_size - 1) {
            break;
        }
        strncat(output + len, p, match.rm_so);
        len += match.rm_so;
        p += match.rm_eo;
    }

    if (len + strlen(p) >= output_size - 1) {
        output[output_size - 1] = '\0';
    } else {
        strcat(output + len, p);
    }

    regfree(&regex);
}

int main() {
    const char *input = " This is a test string with  spaces. ";
    char output[50];

    remove_whitespace(input, output, sizeof(output));
    printf("Result: '%s'\n", output);

    return 0;
}