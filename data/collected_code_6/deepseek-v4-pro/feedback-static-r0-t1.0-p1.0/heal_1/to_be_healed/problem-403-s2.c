#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_url(const char *url) {
    if (url == NULL) return 0;
    
    regex_t regex;
    int ret;
    const char *pattern = "^(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);
    
    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (is_valid_url(argv[1])) {
        printf("Valid URL: %s\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        printf("Invalid URL: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
}