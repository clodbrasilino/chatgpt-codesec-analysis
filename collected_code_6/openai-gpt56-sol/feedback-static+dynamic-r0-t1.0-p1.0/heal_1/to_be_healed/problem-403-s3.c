#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int is_valid_url(const char *url, bool *is_valid)
{
    static const char pattern[] =
        "^(https?|ftp)://"
        "([A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?\\.)+"
        "[A-Za-z]{2,63}"
        "(:[0-9]{1,5})?"
        "(/[A-Za-z0-9._~:/?#\\[\\]@!$&'()*+,;=%-]*)?$";
    regex_t regex;
    int result;

    if (url == NULL || is_valid == NULL) {
        return REG_INVARG;
    }

    *is_valid = false;

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *is_valid = true;
        return 0;
    }

    if (result == REG_NOMATCH) {
        return 0;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    bool valid;
    int result;
    /* Possible weaknesses found:
     *  The scope of the variable 'error_buffer' can be reduced. [variableScope]
     */
    char error_buffer[256];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = is_valid_url(argv[1], &valid);
    if (result != 0) {
        regerror(result, NULL, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex error: %s\n", error_buffer);
        return EXIT_FAILURE;
    }

    printf("%s\n", valid ? "Valid URL" : "Invalid URL");
    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}