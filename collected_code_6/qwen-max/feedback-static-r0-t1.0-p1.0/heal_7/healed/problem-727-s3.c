#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

void sanitize_str(char *str, size_t len) {
    regex_t re;
    if (regcomp(&re, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NOSUB) != 0) {
        char error_message[100];
        regerror(-1, &re, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return;
    }

    size_t pos = 0;
    while (pos < len && regexec(&re, str + pos, 0, NULL, 0) == 0) {
        for (size_t i = pos; i < len; ++i) {
            if (regexec(&re, str + i, 0, NULL, 0) == 0) {
                memmove(str + i, str + i + 1, len - (i - pos) - 1);
                --len;
                --i;
            }
        }
        while (pos < len && !isalnum((unsigned char)str[pos])) {
            ++pos;
        }
    }

    regfree(&re);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_str(input, sizeof(input) - 1);
    printf("%s\n", input);
    return 0;
}