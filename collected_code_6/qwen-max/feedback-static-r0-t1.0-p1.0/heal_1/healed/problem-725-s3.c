#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_quoted_strings(const char *input) {
    regex_t regex;
    regmatch_t match[2];
    char buffer[1024];

    const char *pattern = "\"([^\"]*)\"";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, input, 2, match, 0) == 0) {
        if (match[1].rm_so != -1 && match[1].rm_eo != -1) {
            size_t length = match[1].rm_eo - match[1].rm_so;
            strncpy(buffer, input + match[1].rm_so, length);
            buffer[length] = '\0';
            printf("%s\n", buffer);
        }
        input += match[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *input = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    extract_quoted_strings(input);
    return 0;
}