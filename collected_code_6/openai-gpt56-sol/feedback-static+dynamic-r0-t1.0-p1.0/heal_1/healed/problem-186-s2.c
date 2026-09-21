#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_literal(const char *text, const char *literal, int *error_code)
{
    regex_t regex;
    char *pattern;
    size_t literal_length;
    size_t pattern_capacity;
    size_t i;
    size_t j;
    int result;

    if (error_code == NULL) {
        return false;
    }

    *error_code = 0;

    if (text == NULL || literal == NULL) {
        *error_code = REG_BADPAT;
        return false;
    }

    literal_length = 0;
    while (literal[literal_length] != '\0') {
        if (literal_length >= (SIZE_MAX - 1) / 2) {
            *error_code = REG_ESPACE;
            return false;
        }
        literal_length++;
    }

    pattern_capacity = literal_length * 2 + 1;
    pattern = malloc(pattern_capacity);
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

    if (result != 0 && result != REG_NOMATCH) {
        size_t message_size = regerror(result, &regex, NULL, 0);
        char *message = malloc(message_size);

        if (message != NULL) {
            regerror(result, &regex, message, message_size);
            fprintf(stderr, "Regex execution error: %s\n", message);
            free(message);
        }
    }

    regfree(&regex);
    *error_code = result;

    return result == 0;
}

static void print_regex_error(int error_code, const char *literal)
{
    size_t message_size;
    char *message;

    message_size = regerror(error_code, NULL, NULL, 0);
    if (message_size == 0) {
        fprintf(stderr, "Regex error for \"%s\": error %d\n",
                literal, error_code);
        return;
    }

    message = malloc(message_size);
    if (message == NULL) {
        fprintf(stderr, "Regex error for \"%s\": error %d\n",
                literal, error_code);
        return;
    }

    regerror(error_code, NULL, message, message_size);
    fprintf(stderr, "Regex error for \"%s\": %s\n", literal, message);
    free(message);
}

int main(void)
{
    const char *text =
        "The price is $10.00, and the expression a+b is literal.";
    const char *literals[] = {
        "$10.00",
        "a+b",
        "missing"
    };
    const size_t count = sizeof(literals) / sizeof(literals[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int error_code;
        bool found = contains_literal(text, literals[i], &error_code);

        if (error_code != 0 && error_code != REG_NOMATCH) {
            print_regex_error(error_code, literals[i]);
            return EXIT_FAILURE;
        }

        printf("\"%s\": %s\n", literals[i],
               found ? "found" : "not found");
    }

    return EXIT_SUCCESS;
}