#include <stdio.h>
#include <string.h>
#include <regex.h>

void filter_chars(char *input, char *output) {
    regex_t regex;
    regmatch_t match;
    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;

    if (regcomp(&regex, "[^a-zA-Z0-9]", 0) == 0) {
        for (int i = 0, j = 0; input[i] != '\0'; ++i) {
            reti = regexec(&regex, &input[i], 1, &match, 0);
            if (reti != 0 || match.rm_so != 0) {
                output[j++] = input[i];
            }
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        output[strlen(output)] = '\0';
        regfree(&regex);
    }
}

int main() {
    char input[] = "Hello, World! 123";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[50] = "";

    filter_chars(input, output);

    printf("Filtered: %s\n", output);
    return 0;
}