#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(const char *in_str, char *out_str, size_t max_size) {
    size_t len = strnlen(in_str, max_size - 1);
    if (len > 0) {
        out_str[0] = toupper((unsigned char)in_str[0]);
    }
    for (size_t i = 1; i < len; ++i) {
        out_str[i] = in_str[i];
        if (i > 0 && in_str[i - 1] == ' ' || i < len - 1 && in_str[i + 1] == ' ') {
            out_str[i] = toupper((unsigned char)out_str[i]);
        }
    }
    out_str[len] = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char output[256];
        capitalize_first_last(input, output, sizeof(output));
        printf("Capitalized: %s\n", output);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}