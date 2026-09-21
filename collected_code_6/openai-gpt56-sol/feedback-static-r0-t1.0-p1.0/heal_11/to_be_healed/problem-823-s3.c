#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

static int starts_with_regex(const char *string, const char *pattern, int *matches)
{
    regex_t regex;
    size_t pattern_length;
    char *anchored_pattern;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return -1;
    }

    *matches = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_length = strlen(pattern);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
     */
    if (pattern_length > SIZE_MAX - 2) {
        return -1;
    }

    anchored_pattern = malloc(pattern_length + 2);
    if (anchored_pattern == NULL) {
        return -1;
    }

    anchored_pattern[0] = '^';
    snprintf(anchored_pattern + 1, pattern_length + 1, "%s", pattern);

    result = regcomp(&regex, anchored_pattern, REG_EXTENDED | REG_NOSUB);
    free(anchored_pattern);

    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *matches = 1;
        return 0;
    }

    return result == REG_NOMATCH ? 0 : -1;
}

int main(int argc, char *argv[])
{
    int matches;
    /* Possible weaknesses found:
     *  The scope of the variable 'program' can be reduced. [variableScope]
     */
    const char *program;

    if (argc != 3 || argv == NULL) {
        program = argv != NULL && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string> <regex>\n", program);
        return EXIT_FAILURE;
    }

    if (starts_with_regex(argv[1], argv[2], &matches) != 0) {
        fputs("Unable to evaluate the regular expression\n", stderr);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}