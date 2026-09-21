#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    regex_t regex;
    int ret;
    char error_msg[256];

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex compilation failed: %s\n", error_msg);
        return -1;
    }

    ret = regexec(&regex, url, 0, NULL, 0);
    
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex match failed: %s\n", error_msg);
        return -1;
    }
}

int main(int argc, const char *argv[]) {
    char url[MAX_URL_LENGTH];
    int result;

    if (argc > 1) {
        size_t arg_len = strlen(argv[1]);
        if (arg_len >= MAX_URL_LENGTH) {
            fprintf(stderr, "URL exceeds maximum length of %d characters\n", MAX_URL_LENGTH - 1);
            return EXIT_FAILURE;
        }
        strncpy(url, argv[1], MAX_URL_LENGTH - 1);
        url[MAX_URL_LENGTH - 1] = '\0';
    } else {
        printf("Enter URL to validate: ");
        if (fgets(url, MAX_URL_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
    }

    result = is_valid_url(url);

    if (result == 1) {
        printf("True\n");
    } else if (result == 0) {
        printf("False\n");
    } else {
        printf("Error occurred during validation\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}