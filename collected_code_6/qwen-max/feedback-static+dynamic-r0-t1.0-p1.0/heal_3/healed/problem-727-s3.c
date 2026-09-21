#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

void sanitize_str(char *str, size_t len) {
    regex_t re;
    regmatch_t pmatch[1];
    int status, pos = 0;
    const char *pattern = "[^a-zA-Z0-9]";

    status = regcomp(&re, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[100];
        regerror(status, &re, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return;
    }

    while (regexec(&re, str + pos, 1, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        size_t remaining_len = len - (pos + match_len);
        memmove(str + pos, str + pos + match_len, remaining_len + 1);
        len -= match_len;
        if (len > 0) {
            pos += 1;
        }
    }
    
    regfree(&re);
}

int main() {
    char input[] = "Hello, World! 123";
    size_t input_len = sizeof(input) - 1;
    sanitize_str(input, input_len);
    printf("%s\n", input);
    return 0;
}