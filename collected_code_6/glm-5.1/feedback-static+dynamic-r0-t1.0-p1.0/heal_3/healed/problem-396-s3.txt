#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int check_same_start_end(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    regex_t regex;
    int ret;
    size_t escaped_size = (strchr(".^$*+?\\[({", str[0]) != NULL) ? 3 : 2;
    char escaped_char[escaped_size];

    if (escaped_size == 3) {
        escaped_char[0] = '\\';
        escaped_char[1] = str[0];
        escaped_char[2] = '\0';
    } else {
        escaped_char[0] = str[0];
        escaped_char[1] = '\0';
    }

    size_t full_pattern_len = 1 + strlen(escaped_char) + 2 + strlen(escaped_char) + 1 + 1;
    char full_pattern[full_pattern_len];
    snprintf(full_pattern, full_pattern_len, "^%s.*%s$", escaped_char, escaped_char);

    ret = regcomp(&regex, full_pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int main(int argc, char * const argv[]) {
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