#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_with_colon(char *str)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    char *cursor;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = str;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        cursor[match.rm_so] = ':';
        cursor += match.rm_eo;
    }

    if (ret != REG_NOMATCH) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex execution failed: %s\n", errbuf);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char input[] = "Hello World, this is a test. Goodbye.";

    printf("Original: %s\n", input);

    if (replace_with_colon(input) != 0) {
        fprintf(stderr, "Replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Modified: %s\n", input);

    return EXIT_SUCCESS;
}