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

    return result == REG_NOMATCH ? 0 : result;
}

int main(int argc, char * const argv[])
{
    bool valid;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "url-validator");
        return EXIT_FAILURE;
    }

    result = is_valid_url(argv[1], &valid);
    if (result != 0) {
        size_t required = regerror(result, NULL, NULL, 0);
        char *error_buffer = malloc(required);

        if (error_buffer == NULL) {
            fprintf(stderr, "Regex error %d\n", result);
            return EXIT_FAILURE;
        }

        regerror(result, NULL, error_buffer, required);
        fprintf(stderr, "Regex error: %s\n", error_buffer);
        free(error_buffer);
        return EXIT_FAILURE;
    }

    puts(valid ? "Valid URL" : "Invalid URL");
    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}