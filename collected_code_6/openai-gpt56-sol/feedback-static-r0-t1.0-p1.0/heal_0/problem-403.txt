#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static int is_valid_url(const char *url, bool *is_valid)
{
    static const char pattern[] =
        "^(https?|ftp)://"
        "([A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?\\.)+"
        "[A-Za-z]{2,63}"
        "(:([0-9]{1,5}))?"
        "(/[A-Za-z0-9._~:/?#\\[\\]@!$&'()*+,;=%-]*)?$";
    regex_t regex;
    int status;

    if (url == NULL || is_valid == NULL) {
        return -1;
    }

    *is_valid = false;

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (status == 0) {
        *is_valid = true;
        return 0;
    }

    if (status == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    bool valid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 2;
    }

    if (is_valid_url(argv[1], &valid) != 0) {
        fputs("URL validation failed\n", stderr);
        return 1;
    }

    puts(valid ? "Valid URL" : "Invalid URL");
    return valid ? 0 : 1;
}