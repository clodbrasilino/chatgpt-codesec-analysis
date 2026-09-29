#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ends_with_alphanumeric(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    return isalnum((unsigned char)str[len - 1]) ? 1 : 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (ends_with_alphanumeric(argv[1])) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}