#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048
#define ERROR_MSG_SIZE 256

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_msg[ERROR_MSG_SIZE];

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex compilation failed: %s\n", error_msg);
        return -1;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    
    if (ret == 0) {
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex match failed: %s\n", error_msg);
        regfree(&regex);
        return -1;
    }
}

int main(int argc, const char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char url[MAX_URL_LENGTH];

    if (argc > 1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t arg_len = strlen(argv[1]);
        if (arg_len >= MAX_URL_LENGTH) {
            fprintf(stderr, "URL too long\n");
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(url, argv[1], arg_len + 1);
    } else {
        printf("Enter URL to validate: ");
        if (fgets(url, sizeof(url), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }
        url[strcspn(url, "\n")] = '\0';
    }

    int result = is_valid_url(url);

    if (result == 1) {
        printf("Valid URL\n");
    } else if (result == 0) {
        printf("Invalid URL\n");
    } else {
        printf("Error occurred during validation\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}