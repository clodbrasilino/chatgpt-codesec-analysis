#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *string) {
    if (string == NULL) {
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = match_pattern(argv[1]);
    if (result == 1) {
        printf("Match\n");
    } else if (result == 0) {
        printf("No match\n");
    } else {
        fprintf(stderr, "Regex error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}