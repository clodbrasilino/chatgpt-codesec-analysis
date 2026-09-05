#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_ab(const char *string) {
    if (string == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^ab*$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    
    regfree(&regex);

    if (ret == 0) {
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

    if (match_ab(argv[1])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return 0;
}