#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define URL_PATTERN "^(https?|ftp)://([a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,}(:[0-9]{1,5})?(/[a-zA-Z0-9._~:/?#@!$&'()*+,;=%-]*)?$"
#define ERROR_BUFFER_SIZE 256

static void report_regex_error(int status, const regex_t *regex)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buffer[ERROR_BUFFER_SIZE];
    size_t needed;

    memset(error_buffer, 0, sizeof(error_buffer));
    needed = regerror(status, regex, error_buffer, sizeof(error_buffer));
    error_buffer[sizeof(error_buffer) - 1] = '\0';

    if (needed > sizeof(error_buffer)) {
        fprintf(stderr, "Regex error (truncated): %s\n", error_buffer);
    } else {
        fprintf(stderr, "Regex error: %s\n", error_buffer);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int is_valid_url(const char *url)
{
    regex_t regex;
    int result;
    int compile_status;

    if (url == NULL || url[0] == '\0') {
        return 0;
    }

    compile_status = regcomp(&regex, URL_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (compile_status != 0) {
        report_regex_error(compile_status, &regex);
        return -1;
    }

    result = regexec(&regex, url, 0, NULL, 0);

    if (result == 0) {
        regfree(&regex);
        return 1;
    }

    if (result != REG_NOMATCH) {
        report_regex_error(result, &regex);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
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