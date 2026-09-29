#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    size_t uppercase;
    size_t lowercase;
    size_t numeric;
    size_t special;
} CharacterCounts;

static int matches(const regex_t *regex, unsigned char character)
{
    char text[2] = {(char)character, '\0'};
    return regexec(regex, text, 0, NULL, 0) == 0;
}

static int count_characters(const char *text, CharacterCounts *counts)
{
    regex_t uppercase_regex;
    regex_t lowercase_regex;
    regex_t numeric_regex;
    regex_t special_regex;
    int status;

    if (text == NULL || counts == NULL) {
        return -1;
    }

    *counts = (CharacterCounts){0, 0, 0, 0};

    status = regcomp(&uppercase_regex, "^[[:upper:]]$", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regcomp(&lowercase_regex, "^[[:lower:]]$", REG_EXTENDED);
    if (status != 0) {
        regfree(&uppercase_regex);
        return -1;
    }

    status = regcomp(&numeric_regex, "^[[:digit:]]$", REG_EXTENDED);
    if (status != 0) {
        regfree(&lowercase_regex);
        regfree(&uppercase_regex);
        return -1;
    }

    status = regcomp(&special_regex, "^[^[:alnum:][:space:]]$", REG_EXTENDED);
    if (status != 0) {
        regfree(&numeric_regex);
        regfree(&lowercase_regex);
        regfree(&uppercase_regex);
        return -1;
    }

    for (const unsigned char *current = (const unsigned char *)text;
         *current != '\0';
         ++current) {
        if (matches(&uppercase_regex, *current)) {
            ++counts->uppercase;
        } else if (matches(&lowercase_regex, *current)) {
            ++counts->lowercase;
        } else if (matches(&numeric_regex, *current)) {
            ++counts->numeric;
        } else if (matches(&special_regex, *current)) {
            ++counts->special;
        }
    }

    regfree(&special_regex);
    regfree(&numeric_regex);
    regfree(&lowercase_regex);
    regfree(&uppercase_regex);

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    CharacterCounts counts;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    if (count_characters(input, &counts) != 0) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Uppercase: %zu\n", counts.uppercase);
    printf("Lowercase: %zu\n", counts.lowercase);
    printf("Numeric: %zu\n", counts.numeric);
    printf("Special: %zu\n", counts.special);

    free(input);
    return EXIT_SUCCESS;
}