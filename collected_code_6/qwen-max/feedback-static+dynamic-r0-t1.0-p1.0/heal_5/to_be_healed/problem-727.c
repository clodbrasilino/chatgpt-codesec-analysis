#include <stdio.h>
#include <string.h>
#include <regex.h>

void filter_chars(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, "[^a-zA-Z0-9]", 0) == 0) {
        for (int i = 0, j = 0; input[i] != '\0' && j < output_size - 1; ++i) {
            int reti = regexec(&regex, &input[i], 1, &match, 0);
            if (reti != 0 || match.rm_so != 0) {
                output[j++] = input[i];
            }
        }
        output[output_size - 1] = '\0';
        regfree(&regex);
    } else {
        memset(output, 0, output_size);
    }
}

int main() {
    const char input[] = "Hello, World! 123";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[50];

    filter_chars(input, output, sizeof(output));
    printf("Filtered: %s\n", output);

    return 0;
}