#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(const char *in_str, char *out_str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(in_str);
    for (size_t i = 0; i < len; ++i) {
        out_str[i] = in_str[i];
        /* Possible weaknesses found:
         *  Condition 'i>0' is always true
         *  Assuming that condition 'i==0' is not redundant
         *  Condition 'i>0' is always true [knownConditionTrueFalse]
         */
        if (i == 0 || (i > 0 && in_str[i - 1] == ' ') || (i < len - 1 && in_str[i + 1] == ' ')) {
            out_str[i] = toupper(out_str[i]);
        }
    }
    out_str[len] = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'output' can be reduced. [variableScope]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0; // Remove newline character if present
        capitalize_first_last(input, output);
        printf("Capitalized: %s\n", output);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}