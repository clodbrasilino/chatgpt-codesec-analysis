#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0 ? 1 : 0;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    if (len >= 4096) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    char *buf = malloc(len + 1);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buf, argv[1], len + 1);
    buf[len] = '\0';

    int result = match_pattern(buf);
    free(buf);

    if (result == -1) {
        fprintf(stderr, "Regex compilation failed\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}