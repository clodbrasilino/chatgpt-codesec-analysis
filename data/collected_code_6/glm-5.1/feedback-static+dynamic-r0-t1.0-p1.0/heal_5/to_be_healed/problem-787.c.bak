#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool match_a_three_b(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len < 4) {
        return false;
    }

    const char *end = str + len - 3;

    while (str < end) {
        if (str[0] == 'a' && str[1] == 'b' && str[2] == 'b' && str[3] == 'b') {
            return true;
        }
        str++;
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
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