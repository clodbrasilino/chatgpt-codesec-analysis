#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define URL_PATTERN "^(https?|ftp)://([a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,}(:[0-9]{1,5})?(/[a-zA-Z0-9._~:/?#@!$&'()*+,;=%-]*)?$"
#define MAX_URL_LENGTH 2048

static void print_regex_error(int compile_status, const regex_t *regex)
{
    size_t needed;
    char *error_buffer;

    needed = regerror(compile_status, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "Regex compilation failed: unknown error\n");
        return;
    }

    error_buffer = malloc(needed);
    if (error_buffer == NULL) {
        fprintf(stderr, "Regex compilation failed: unable to allocate error buffer\n");
        return;
    }

    regerror(compile_status, regex, error_buffer, needed);
    error_buffer[needed - 1] = '\0';
    fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
    free(error_buffer);
}

int is_valid_url(const char *url)
{
    regex_t regex;
    int result;
    int compile_status;
    size_t url_length;

    if (url == NULL) {
        return 0;
    }

    url_length = strnlen(url, MAX_URL_LENGTH + 1);
    if (url_length == 0 || url_length > MAX_URL_LENGTH) {
        return 0;
    }

    compile_status = regcomp(&regex, URL_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (compile_status != 0) {
        print_regex_error(compile_status, &regex);
        return -1;
    }

    result = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return 1;
    }

    return 0;
}

int main(void)
{
    const char *test_urls[] = {
        "https://www.example.com",
        "http://example.com/path/to/page?query=value",
        "ftp://files.example.org:2121/downloads",
        "https://sub.domain.example.co.uk/page#section",
        "not_a_url",
        "http://",
        "://missing-scheme.com",
        "https://invalid..domain.com",
        ""
    };
    size_t count;
    size_t i;

    count = sizeof(test_urls) / sizeof(test_urls[0]);

    for (i = 0; i < count; i++) {
        int status = is_valid_url(test_urls[i]);
        if (status < 0) {
            fprintf(stderr, "Error validating URL: %s\n", test_urls[i]);
            return EXIT_FAILURE;
        }
        if (status == 1) {
            printf("VALID:   %s\n", test_urls[i]);
        } else {
            printf("INVALID: %s\n", test_urls[i]);
        }
    }

    return EXIT_SUCCESS;
}