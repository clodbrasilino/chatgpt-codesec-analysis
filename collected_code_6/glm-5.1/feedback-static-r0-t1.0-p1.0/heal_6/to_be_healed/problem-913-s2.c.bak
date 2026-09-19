#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_number_at_end(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    const char *ptr = str + len - 1;

    while (ptr >= str && isdigit((unsigned char)*ptr)) {
        ptr--;
    }

    if (ptr != str + len - 1 && (ptr < str || !isdigit((unsigned char)*ptr))) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = check_number_at_end(argv[1]);
    printf("%d\n", result);

    return 0;
}