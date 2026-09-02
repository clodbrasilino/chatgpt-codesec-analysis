#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void sanitize_string(char *input) {
    regex_t re;
    char *output = NULL;
    size_t output_size;

    if (regcomp(&re, "[^a-zA-Z0-9]", REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    regmatch_t pmatch[1];
    output_size = strlen(input) + 1;
    output = (char *)malloc(output_size);
    if (output == NULL) {
        regfree(&re);
        return;
    }

    int i = 0, j = 0;
    while (i < (int)output_size - 1) {
        if (regexec(&re, input + i, 1, pmatch, 0) != 0) {
            output[j++] = input[i++];
        } else {
            i += pmatch[0].rm_eo;
        }
    }
    output[j] = '\0';

    strcpy(input, output);
    free(output);
    regfree(&re);
}

int main() {
    char input[] = "Test123!@# with Special$%^&*()_+Characters";
    printf("Original: %s\n", input);
    sanitize_string(input);
    printf("Sanitized: %s\n", input);
    return 0;
}