#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *errbuf = malloc(needed);

    if (errbuf != NULL) {
        regerror(errcode, regex, errbuf, needed);
        fprintf(stderr, "%s: %s\n", context, errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "%s: unable to allocate error buffer\n", context);
    }
}

char *extract_quoted_value(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    char *result = NULL;
    int ret;
    size_t input_len;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return NULL;
    }

    ret = regexec(&regex, input, 2, matches, 0);
    if (ret == 0) {
        if (matches[1].rm_so >= 0 &&
            matches[1].rm_eo >= matches[1].rm_so &&
            (size_t)matches[1].rm_eo <= input_len) {
            size_t len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
            result = malloc(len + 1);
            if (result != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, input + matches[1].rm_so, len);
                result[len] = '\0';
            } else {
                fprintf(stderr, "Memory allocation failed\n");
            }
        }
    } else if (ret != REG_NOMATCH) {
        print_regex_error(ret, &regex, "Regex execution failed");
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_string = "The value is \"hello world\" in this string";
    char *value;

    value = extract_quoted_value(test_string);
    if (value != NULL) {
        printf("Extracted value: %s\n", value);
        free(value);
    } else {
        printf("No quoted value found\n");
    }

    return EXIT_SUCCESS;
}