#include <stdio.h>
#include <regex.h>
#include <string.h>

int replace_chars_with_colon(char *str, size_t str_len) {
    regex_t reg;
    if (regcomp(&reg, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) return -1;

    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int pos = 0;

    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%.*s:%.*s", (int)match_len, str + pos, (int)(str_len - (pos + match_len)), str + pos + match_len);
        size_t new_len = strnlen(buffer, sizeof(buffer));

        memmove(str + pos + new_len, str + pos + pmatch[0].rm_eo, str_len - (pos + pmatch[0].rm_eo) + 1);
        memmove(str + pos, buffer, new_len);

        pos += new_len - match_len;
        str_len += new_len - match_len;
    }

    regfree(&reg);
    return 0;
}

int main() {
    char input[] = "Hello, world. This is a test, of the system.";
    size_t input_len = sizeof(input) - 1;
    if (replace_chars_with_colon(input, input_len) == 0) {
        printf("%s\n", input);
    } else {
        printf("Replacement failed.\n");
    }
    return 0;
}