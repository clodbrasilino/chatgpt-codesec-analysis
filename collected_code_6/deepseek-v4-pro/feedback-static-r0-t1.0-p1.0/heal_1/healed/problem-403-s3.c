#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048
#define MAX_MATCHES 1
#define ERROR_MSG_SIZE 256

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    regex_t regex;
    int ret;
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
        regfree(&regex);
        fprintf(stderr, "Regex match failed: %s\n", error_msg);
        return -1;
    }
}

int main(int argc, const char *argv[]) {
    char url[MAX_URL_LENGTH];

    if (argc > 1) {
        strncpy(url, argv[1], MAX_URL_LENGTH - 1);
        url[MAX_URL_LENGTH - 1] = '\0';
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