#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048
#define ERROR_MSG_SIZE 256
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int is_valid_url(const char *url) {
    if (url == NULL) {
        return 0;
    }

    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    regex_t regex;
    int ret;
    char *error_msg = NULL;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        size_t err_size = regerror(ret, &regex, NULL, 0);
        error_msg = malloc(err_size);
        if (error_msg != NULL) {
            regerror(ret, &regex, error_msg, err_size);
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
        size_t err_size = regerror(ret, &regex, NULL, 0);
        error_msg = malloc(err_size);
        if (error_msg != NULL) {
            regerror(ret, &regex, error_msg, err_size);
            fprintf(stderr, "Regex match failed: %s\n", error_msg);
            free(error_msg);
        } else {
            fprintf(stderr, "Regex match failed\n");
        }
        regfree(&regex);
        return -1;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    char *url = NULL;

    if (argc > 1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t arg_len = strlen(argv[1]);
        if (arg_len >= MAX_URL_LENGTH) {
            fprintf(stderr, "URL exceeds maximum length of %d characters\n", MAX_URL_LENGTH - 1);
            return EXIT_FAILURE;
        }
        url = malloc(arg_len + 1);
        if (url == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(url, argv[1]);
    } else {
        url = malloc(MAX_URL_LENGTH);
        if (url == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        printf("Enter URL to validate: ");
        if (fgets(url, MAX_URL_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            free(url);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
    }

    int result = is_valid_url(url);

    if (result == 1) {
        printf("True\n");
    } else if (result == 0) {
        printf("False\n");
    } else {
        printf("Error occurred during validation\n");
        free(url);
        return EXIT_FAILURE;
    }

    free(url);
    return EXIT_SUCCESS;
}