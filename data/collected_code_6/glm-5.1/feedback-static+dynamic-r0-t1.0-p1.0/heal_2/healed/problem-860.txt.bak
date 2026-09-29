#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
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

    if (isalnum((unsigned char)str[len - 1])) {
        return 1;
    }

    return 0;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = ends_with_alphanumeric(argv[1]);
    printf("%d\n", result);

    return 0;
}