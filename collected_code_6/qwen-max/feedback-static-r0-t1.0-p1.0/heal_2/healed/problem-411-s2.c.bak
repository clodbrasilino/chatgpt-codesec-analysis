#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    static char output[512];
    memset(output, 0, sizeof(output));
    regex_t preg;
    regmatch_t pmatch[2];
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t dst = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            int nmatch = 2;
            if (regexec(&preg, &input[i], nmatch, pmatch, 0) == 0) {
                output[dst++] = toupper(input[i + 1]);
                i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
            } else {
                output[dst++] = input[i];
            }
        }
        regfree(&preg);
    }
    return output;
}

int main() {
    const char *snake = "this_is_snake_case";
    char *camel = snake_to_camel(snake);
    printf("Camel case: %s\n", camel);
    return 0;
}