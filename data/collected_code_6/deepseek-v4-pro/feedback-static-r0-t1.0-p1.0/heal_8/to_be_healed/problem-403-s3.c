#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

static int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    size_t url_len = strnlen(url, MAX_URL_LENGTH);
    if (url_len >= MAX_URL_LENGTH) {
        return -1;
    }

    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    regex_t regex;
    int ret;
    char *error_msg = NULL;
    size_t errbuf_size;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        errbuf_size = regerror(ret, &regex, NULL, 0);
        error_msg = (char *)malloc(errbuf_size);
        if (error_msg != NULL) {
            regerror(ret, &regex, error_msg, errbuf_size);
            fprintf(stderr, "Regex compilation failed: %s\n", error_msg);
            free(error_msg);
        } else {
            fprintf(stderr, "Regex compilation failed\n");
        }
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
        errbuf_size = regerror(ret, &regex, NULL, 0);
        error_msg = (char *)malloc(errbuf_size);
        if (error_msg != NULL) {
            regerror(ret, &regex, error_msg, errbuf_size);
            fprintf(stderr, "Regex match failed: %s\n", error_msg);
            free(error_msg);
        } else {
            fprintf(stderr, "Regex match failed\n");
        }
        regfree(&regex);
        return -1;
    }
}

int main(int argc, const char *argv[]) {
    char *url = NULL;

    url = (char *)calloc(MAX_URL_LENGTH, sizeof(char));
    if (url == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        if (argv[1] == NULL) {
            fprintf(stderr, "Invalid argument\n");
            free(url);
            return EXIT_FAILURE;
        }
        size_t arg_len = strnlen(argv[1], MAX_URL_LENGTH);
        if (arg_len >= MAX_URL_LENGTH) {
            fprintf(stderr, "URL too long\n");
            free(url);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(url, argv[1], arg_len);
        url[arg_len] = '\0';
    } else {
        printf("Enter URL to validate: ");
        if (fgets(url, MAX_URL_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            free(url);
            return EXIT_FAILURE;
        }
        size_t len = strcspn(url, "\n");
        if (len < MAX_URL_LENGTH) {
            url[len] = '\0';
        } else {
            url[MAX_URL_LENGTH - 1] = '\0';
        }
    }

    int result = is_valid_url(url);

    free(url);

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