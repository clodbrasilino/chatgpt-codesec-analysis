#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str, size_t len) {
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *ptr = str, *end = str + len;

    while (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        memmove(ptr + 1, ptr + match_len, end - (ptr + match_len) + 1);
        *ptr = ':';
        ptr += match_len + 1;
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello, World. This is a test string.";
    replace_chars(input, sizeof(input) - 1);
    printf("%s\n", input);
    return 0;
}