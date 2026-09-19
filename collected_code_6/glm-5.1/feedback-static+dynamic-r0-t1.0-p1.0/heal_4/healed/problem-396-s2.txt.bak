#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_ends_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    size_t len = strlen(str);
    return str[0] == str[len - 1];
}

int main(int argc, char * const argv[static argc]) {
    if (argc < 2) {
        return 1;
    }

    if (starts_ends_same(argv[1])) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}