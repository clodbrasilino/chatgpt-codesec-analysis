#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define URL_PATTERN "^(https?|ftp)://([a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z][a-zA-Z]+(:[0-9]{1,5})?(/[a-zA-Z0-9._~:/?#@!$&'()*+,;=%-]*)?$"

static void report_regex_error(int status, const regex_t *regex)
{
    size_t needed;
    char *error_buffer;

    needed = regerror(status, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "Regex error: unknown error\n");
        return;
    }

    error_buffer = calloc(needed, sizeof(char));
    if (error_buffer == NULL) {
        fprintf(stderr, "Regex error: unable to allocate error buffer\n");
        return;
    }

    regerror(status, regex, error_buffer, needed);
    error_buffer[needed - 1] = '\0';
    fprintf(stderr, "Regex error: %s\n", error_buffer);
    free(error_buffer);
}

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
    regfree(&regex);

    if (result == 0) {
        return 1;
    }

    if (result != REG_NOMATCH) {
        return -1;
    }

    return 0;
}

static int validate_and_print(const char *url)
{
    int status = is_valid_url(url);

    if (status < 0) {
        fprintf(stderr, "Error validating URL: %s\n", url);
        return -1;
    }

    if (status == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (validate_and_print(argv[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (validate_and_print(buffer) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}