#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_non_alphanumeric(const char *input, char *output) {
    regex_t regex;
    regmatch_t match;
    const char *cursor = input;
    size_t output_index = 0;

    int ret = regcomp(&regex, "[[:alnum:]]", REG_EXTENDED);
    if (ret) {
        output[0] = '\0';
        return;
    }

    while (*cursor && regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }
        output[output_index++] = cursor[match.rm_so];
        cursor += match.rm_so + 1;
    }

    output[output_index] = '\0';
    regfree(&regex);
}

int main(void) {
    const char *input = "Hello, World! 123 ...";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];

    remove_non_alphanumeric(input, output);
    printf("Input: %s\n", input);
    printf("Output: %s\n", output);

    return 0;
}