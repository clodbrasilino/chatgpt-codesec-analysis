#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_chars_with_colon(char *str) {
    if (str == NULL) {
        return -1;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *pattern = "[ ,.]";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return -1;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        str[pmatch[0].rm_so] = ':';
        str += pmatch[0].rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    char text[] = "Hello, world. This is a test string.";
    
    printf("Original: %s\n", text);
    
    if (replace_chars_with_colon(text) == 0) {
        printf("Modified: %s\n", text);
    } else {
        fprintf(stderr, "Regex compilation or execution failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}