#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* input) {
    if (!input) {
        return NULL;
    }

    char* result = strdup(input);
    if (!result) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    regmatch_t pmatch[1];
    char* p = result;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        p[pmatch[0].rm_so] = ':';
        p += pmatch[0].rm_eo;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char* sample_text = "This is a test, with spaces. And dots.";
    char* modified_text = replace_with_colon(sample_text);

    if (modified_text) {
        printf("%s\n", modified_text);
        free(modified_text);
    } else {
        fprintf(stderr, "Error processing the string.\n");
        return 1;
    }

    return 0;
}