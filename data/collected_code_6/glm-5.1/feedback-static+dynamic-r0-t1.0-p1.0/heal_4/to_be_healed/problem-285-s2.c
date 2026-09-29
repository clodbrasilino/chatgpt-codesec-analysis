#include <stdio.h>
#include <string.h>
#include <regex.h>

int match_a_bbb(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int ret = regcomp(&regex, "^ab{2,3}$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    int match = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        return 1;
    }
    
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (match_a_bbb(argv[1])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return 0;
}