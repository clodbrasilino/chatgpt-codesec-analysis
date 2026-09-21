#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

void sanitize_str(char *str, size_t len) {
    regex_t re;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]";

    if (regcomp(&re, pattern, REG_EXTENDED)) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[100];
        regerror(errno, &re, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return;
    }

    for (size_t pos = 0; pos < len; ) {
        if (regexec(&re, str + pos, 1, pmatch, 0) == 0) {
            size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            memmove(str + pos, str + pos + match_len, len - pos - match_len + 1);
            len -= match_len;
        } else {
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