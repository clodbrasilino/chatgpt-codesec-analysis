#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int validate_url(const char *url) {
    regex_t regex;
    const char *pattern = "^((http|https)://)?(www.)?[a-z0-9]+([-.]{1}[a-z0-9]+)*.[a-z]{2,5}(:[0-9]{1,5})?(/.*$)?";
    int compilation_error = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (compilation_error) {
        printf("Could not compile regex.\n");
        return -1;
    }
    int validation_error = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    if (validation_error == 0) {
        return 1;
    } else if (validation_error == REG_NOMATCH) {
        return 0;
    } else {
        char error_message[256];
        regerror(validation_error, &regex, error_message, sizeof(error_message));
        printf("Regex match failed: %s\n", error_message);
        return -1;
    }
}

int main() {
    // Valid URL Test
    const char *url1 = "http://www.google.com";
    int result = validate_url(url1);
    if (result == 1) {
        printf("Valid URL.\n");
    } else if (result == 0) {
        printf("Invalid URL.\n");
    } else {
        printf("An error occurred.\n");
    }

    // Invalid URL Test
    const char *url2 = "http:/www.google.com";
    result = validate_url(url2);
    if (result == 1) {
        printf("Valid URL.\n");
    } else if (result == 0) {
        printf("Invalid URL.\n");
    } else {
        printf("An error occurred.\n");
    }

    return 0;
}