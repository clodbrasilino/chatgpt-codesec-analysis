#include <stdio.h>
#include <string.h>
#include <regex.h>

void filter_chars(char *input, char *output) {
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, "[^a-zA-Z0-9]", 0) == 0) {
        for (int i = 0, j = 0, reti; input[i] != '\0'; ++i) {
            reti = regexec(&regex, &input[i], 1, &match, 0);
            if (reti != 0 || match.rm_so != 0) {
                output[j++] = input[i];
            }
        }
        output[strlen(output)] = '\0';
        regfree(&regex);
    }
}

int main() {
    char input[] = "Hello, World! 123";
    char output[50] = "";

    filter_chars(input, output);

    printf("Filtered: %s\n", output);
    return 0;
}