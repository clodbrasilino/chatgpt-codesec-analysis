#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT 256
#define ERRBUF_SIZE 128

int count_matches(const char *pattern, const char *text, int *count)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;
    int exec_flags;

    if (pattern == NULL || text == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char errbuf[ERRBUF_SIZE];
        memset(errbuf, 0, sizeof(errbuf));
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    exec_flags = 0;
    while (regexec(&regex, cursor, 1, &match, exec_flags) == 0) {
        if (match.rm_eo == match.rm_so) {
            break;
        }
        (*count)++;
        cursor += match.rm_eo;
        exec_flags = REG_NOTBOL;
    }

    regfree(&regex);
    return 0;
}

int analyze_string(const char *input)
{
    int upper = 0;
    int lower = 0;
    int digits = 0;
    int special = 0;

    if (input == NULL) {
        return -1;
    }

    if (count_matches("[A-Z]", input, &upper) != 0) {
        return -1;
    }
    if (count_matches("[a-z]", input, &lower) != 0) {
        return -1;
    }
    if (count_matches("[0-9]", input, &digits) != 0) {
        return -1;
    }
    if (count_matches("[^A-Za-z0-9]", input, &special) != 0) {
        return -1;
    }

    printf("Uppercase letters : %d\n", upper);
    printf("Lowercase letters : %d\n", lower);
    printf("Numeric digits    : %d\n", digits);
    printf("Special characters: %d\n", special);

    return 0;
}

int main(void)
{
    char input[MAX_INPUT];
    size_t len;

    memset(input, 0, sizeof(input));

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (analyze_string(input) != 0) {
        fprintf(stderr, "Analysis failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}