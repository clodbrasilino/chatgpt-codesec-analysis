#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_a_three_b(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strnlen(str, 4);
    if (len < 4) {
        return false;
    }

    const char *p = str;

    while (*p != '\0' && *(p + 1) != '\0' && *(p + 2) != '\0' && *(p + 3) != '\0') {
        if (*p == 'a' && *(p + 1) == 'b' && *(p + 2) == 'b' && *(p + 3) == 'b') {
            return true;
        }
        p++;
    }

    return false;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    bool result = match_a_three_b(argv[1]);

    if (result) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}