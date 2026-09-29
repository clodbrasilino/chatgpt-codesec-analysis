#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_literal(const char *text, const char *literal, int *error_code)
{
    regex_t regex;
    char *pattern;
    size_t literal_length;
    size_t pattern_length;
    size_t i;
    size_t j;
    int result;

    if (text == NULL || literal == NULL || error_code == NULL) {
        return false;
    }

    literal_length = 0;
    while (literal[literal_length] != '\0') {
        if (literal_length == SIZE_MAX - 1) {
            *error_code = REG_ESPACE;
            return false;
        }
        literal_length++;
    }

    if (literal_length > (SIZE_MAX - 1) / 2) {
        *error_code = REG_ESPACE;
        return false;
    }

    pattern_length = literal_length * 2 + 1;
    pattern = malloc(pattern_length);
    if (pattern == NULL) {
        *error_code = REG_ESPACE;
        return false;
    }

    j = 0;
    for (i = 0; i < literal_length; i++) {
        switch (literal[i]) {
            case '.':
            case '^':
            case '$':
            case '*':
            case '+':
            case '?':
            case '(':
            case ')':
            case '[':
            case ']':
            case '{':
            case '}':
            case '|':
            case '\\':
                pattern[j++] = '\\';
                break;
            default:
                break;
        }
        pattern[j++] = literal[i];
    }
    pattern[j] = '\0';

    result = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);

    if (result != 0) {
        *error_code = result;
        return false;
    }

    result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *error_code = 0;
        return true;
    }

    *error_code = result;
    return false;
}

int main(void)
{
    const char *text = "The price is $10.00, and the expression a+b is literal.";
    const char *literals[] = {"$10.00", "a+b", "missing"};
    const size_t count = sizeof(literals) / sizeof(literals[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int error_code = 0;
        bool found = contains_literal(text, literals[i], &error_code);

        if (error_code != 0 && error_code != REG_NOMATCH) {
            char message[256];

            regerror(error_code, NULL, message, sizeof(message));
            fprintf(stderr, "Regex error for \"%s\": %s\n", literals[i], message);
            return EXIT_FAILURE;
        }

        printf("\"%s\": %s\n", literals[i], found ? "found" : "not found");
    }

    return EXIT_SUCCESS;
}