#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int check_same_start_end(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char escaped_char[4];
    memset(escaped_char, 0, sizeof(escaped_char));

    if (str[0] == '\\') {
        escaped_char[0] = '\\';
        escaped_char[1] = '\\';
        escaped_char[2] = '\\';
        escaped_char[3] = '\\';
    } else if (strchr(".^$*+?()[{|", str[0]) != NULL) {
        escaped_char[0] = '\\';
        escaped_char[1] = str[0];
        escaped_char[2] = '\\';
        escaped_char[3] = str[0];
    } else {
        escaped_char[0] = str[0];
        escaped_char[1] = str[0];
    }

    regex_t regex;
    int ret;
    char *pattern = NULL;

    if (asprintf(&pattern, "^(%s).*\\1$", escaped_char) < 0) {
        return 0;
    }

    size_t max_len = 1024 * 1024;
    size_t len = strnlen(str, max_len + 1);
    if (len > max_len) {
        free(pattern);
        return 0;
    }
    
    char *buf = malloc(len + 1);
    if (buf == NULL) {
        free(pattern);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf, str, len);
    buf[len] = '\0';

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        free(pattern);
        free(buf);
        return 0;
    }

    ret = regexec(&regex, buf, 0, NULL, 0);
    regfree(&regex);
    free(pattern);
    free(buf);

    return ret == 0;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (check_same_start_end(argv[1])) {
        printf("Match\n");
    } else {
        printf("No Match\n");
    }

    return EXIT_SUCCESS;
}