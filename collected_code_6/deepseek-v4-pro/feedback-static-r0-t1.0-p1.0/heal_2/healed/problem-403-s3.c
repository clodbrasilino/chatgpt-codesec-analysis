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

    size_t url_len = strlen(url);
    if (url_len >= MAX_URL_LENGTH) {
        return -1;
    }

    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    regex_t regex;
    int ret;
    char error_msg[ERROR_MSG_SIZE] = {0};

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_msg, sizeof(error_msg) - 1);
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
        regerror(ret, &regex, error_msg, sizeof(error_msg) - 1);
        fprintf(stderr, "Regex match failed: %s\n", error_msg);
        regfree(&regex);
        return -1;
    }
}

int main(int argc, const char *argv[]) {
    char url[MAX_URL_LENGTH] = {0};

    if (argc > 1) {
        size_t arg_len = strnlen(argv[1], MAX_URL_LENGTH);
        if (arg_len >= MAX_URL_LENGTH) {
            fprintf(stderr, "URL too long\n");
            return EXIT_FAILURE;
        }
        strncpy(url, argv[1], MAX_URL_LENGTH - 1);
        url[MAX_URL_LENGTH - 1] = '\0';
    } else {
        printf("Enter URL to validate: ");
        if (fgets(url, (int)sizeof(url), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }
        size_t len = strcspn(url, "\n");
        if (len < sizeof(url)) {
            url[len] = '\0';
        }
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