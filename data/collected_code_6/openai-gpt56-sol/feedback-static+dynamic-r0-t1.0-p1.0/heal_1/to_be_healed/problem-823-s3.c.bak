#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

static int starts_with_regex(const char *string, const char *pattern, int *matches)
{
    regex_t regex;
    regmatch_t match;
    char *anchored_pattern;
    size_t pattern_length;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    pattern_length = strlen(pattern);
    if (pattern_length > SIZE_MAX - 2) {
        return -1;
    }

    anchored_pattern = malloc(pattern_length + 2);
    if (anchored_pattern == NULL) {
        return -1;
    }

    anchored_pattern[0] = '^';
    /* Possible weaknesses found:
     *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'memcpy'
     *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
     *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
     */
    memcpy(anchored_pattern + 1, pattern, pattern_length + 1);

    result = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);

    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, string, 1, &match, 0);
    regfree(&regex);

    if (result == 0) {
        *matches = 1;
        return 0;
    }

    if (result == REG_NOMATCH) {
        *matches = 0;
        return 0;
    }

    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int matches;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <regex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (starts_with_regex(argv[1], argv[2], &matches) != 0) {
        fprintf(stderr, "Unable to evaluate the regular expression\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", matches ? "true" : "false");
    return EXIT_SUCCESS;
}