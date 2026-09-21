#include <stdio.h>
#include <regex.h>
#include <string.h>

int replace_chars_with_colon(char *str) {
    regex_t reg;
    if (regcomp(&reg, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) return -1;

    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int pos = 0;

    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%.*s:%s", (int)match_len, str + pos, str + pos + match_len);
        size_t new_len = strlen(buffer);
        memmove(str + pos + new_len, str + pos + pmatch[0].rm_eo, strlen(str + pos + pmatch[0].rm_eo) + 1);
        memcpy(str + pos, buffer, new_len);
        pos += new_len - match_len;
    }

    regfree(&reg);
    return 0;
}

int main() {
    char input[] = "Hello, world. This is a test, of the system.";
    if (replace_chars_with_colon(input) == 0) {
        printf("%s\n", input);
    } else {
        printf("Replacement failed.\n");
    }
    return 0;
}