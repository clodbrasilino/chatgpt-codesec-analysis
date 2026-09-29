#include <stdio.h>
#include <string.h>
#include <regex.h>

void filter_chars(const char *input, char *output, size_t output_size) {
    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", 0) == 0) {
        for (size_t i = 0, j = 0; input[i] != '\0' && j < output_size - 1; ++i) {
            if (regexec(&regex, &input[i], 1, NULL, 0) != 0) {
                output[j++] = input[i];
            }
        }
        output[output_size - 1] = '\0';
        regfree(&regex);
    } else {
        output[0] = '\0';
    }
}

int main() {
    const char input[] = "Hello, World! 123";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[50] = "";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len >= sizeof(output)) {
        output[0] = '\0';
    } else {
        filter_chars(input, output, sizeof(output));
    }

    printf("Filtered: %s\n", output);
    return 0;
}