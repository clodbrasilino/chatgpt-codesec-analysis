#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void filter_alphanumeric(const char *input, char **output) {
    if (input == NULL || output == NULL) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        *output = NULL;
        return;
    }

    size_t len = strlen(input);
    *output = (char *)malloc(len + 1);
    if (*output == NULL) {
        regfree(&regex);
        return;
    }

    regmatch_t pmatch[1];
    const char *p = input;
    char *out_p = *output;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        memcpy(out_p, p, match_start);
        out_p += match_start;
        
        p += match_end;
    }

    strcpy(out_p, p);
    
    regfree(&regex);
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    filter_alphanumeric(input, &output);

    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Filtered: %s\n", output);
        free(output);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}