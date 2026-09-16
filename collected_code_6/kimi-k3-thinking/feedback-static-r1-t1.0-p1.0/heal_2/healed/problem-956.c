#include <stdio.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *pattern, const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_buffer[256];
        regerror(status, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Could not compile regex: %s\n", error_buffer);
        return -1;
    }

    status = regexec(&regex, cursor, 1, &match, 0);
    if (status == 0) {
        printf("Match found at offset %ld, length %ld\n",
               (long)match.rm_so, (long)(match.rm_eo - match.rm_so));
        regfree(&regex);
        return 0;
    } else if (status == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        char error_buffer[256];
        regerror(status, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex match failed: %s\n", error_buffer);
    }

    regfree(&regex);
    return 1;
}

int main(void)
{
    const char *pattern = "world";
    const char *text = "hello world 123";

    return match_pattern(pattern, text);
}