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
        char *errbuf = calloc(ERRBUF_SIZE, sizeof(char));
        if (errbuf == NULL) {
            fprintf(stderr, "Regex compilation failed and memory allocation failed\n");
            return -1;
        }
        regerror(ret, &regex, errbuf, ERRBUF_SIZE - 1);
        errbuf[ERRBUF_SIZE - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        free(errbuf);
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
    char *input;
    size_t len;

    input = calloc(MAX_INPUT, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[MAX_INPUT - 1] = '\0';

    len = strnlen(input, MAX_INPUT);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (analyze_string(input) != 0) {
        fprintf(stderr, "Analysis failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}