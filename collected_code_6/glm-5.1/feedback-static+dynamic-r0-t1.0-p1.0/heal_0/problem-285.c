#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

int match_a_two_three_b(const char *string) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^ab{2,3}$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (match_a_two_three_b(argv[1])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return EXIT_SUCCESS;
}