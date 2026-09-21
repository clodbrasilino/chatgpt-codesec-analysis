#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_a_three_b(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len < 4) {
        return false;
    }

    const char *p = str;
    const char *end = str + len - 3;

    while (p <= end) {
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