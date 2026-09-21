#define _POSIX_C_SOURCE 200809L
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

    size_t len = strnlen(input, 8192);
    *output = (char *)malloc(len + 1);
    if (*output == NULL) {
        regfree(&regex);
        return;
    }

    regmatch_t pmatch[1];
    const char *p = input;
    char *out_ptr = *output;
    size_t dest_size = len + 1;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_so;
        
        if (match_len > dest_size - 1) {
            match_len = dest_size - 1;
        }
        
        memcpy(out_ptr, p, match_len);
        out_ptr += match_len;
        dest_size -= match_len;
        
        p += pmatch[0].rm_eo;
    }

    snprintf(out_ptr, dest_size, "%s", p);
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
        printf("Failed to filter string.\n");
    }

    return 0;
}