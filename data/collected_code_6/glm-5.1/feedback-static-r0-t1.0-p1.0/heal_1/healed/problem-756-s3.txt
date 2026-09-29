#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_a_followed_by_zero_or_one_b(const char *str) {
    if (str == NULL || str[0] != 'a') {
        return false;
    }

    if (str[1] == 'b') {
        return str[2] == '\0';
    }

    return str[1] == '\0';
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    bool result = match_a_followed_by_zero_or_one_b(argv[1]);
    printf("%d\n", result);

    return 0;
}