#include <stdio.h>
#include <string.h>
#include <regex.h>

void sanitize_str(char *str, size_t size) {
    regex_t re;
    regmatch_t pmatch[1];
    int status, pos = 0;
    const char *pattern = "[^a-zA-Z0-9]";

    status = regcomp(&re, pattern, REG_EXTENDED);
    if (status != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[100];
        regerror(status, &re, error_message, 100);
        return;
    }

    while (pos < size && regexec(&re, str + pos, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (pmatch[0].rm_eo + pos < size) {
            memmove(str + pos + len, str + pos + pmatch[0].rm_eo, size - (pos + pmatch[0].rm_eo));
        }
        size -= len;
        str[size] = '\0';
    }

    regfree(&re);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_str(input, sizeof(input) - 1);
    printf("%s\n", input);
    return 0;
}