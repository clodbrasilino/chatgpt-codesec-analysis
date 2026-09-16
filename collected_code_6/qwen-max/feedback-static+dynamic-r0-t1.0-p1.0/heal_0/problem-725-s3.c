#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_quoted_strings(const char *input) {
    int error;
    regex_t regex;
    regmatch_t match[1];
    char buffer[1024];

    const char *pattern = "\"([^\"]*)\"";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, input, 1, match, 0) == 0) {
        strncpy(buffer, input + match[1].rm_so, match[1].rm_eo - match[1].rm_so);
        buffer[match[1].rm_eo - match[1].rm_so] = '\0';
        printf("%s\n", buffer);
        input += match[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *input = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    extract_quoted_strings(input);
    return 0;
}