#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool all_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool seen[UCHAR_MAX + 1] = { false };

    for (const char *p = str; *p != '\0'; ++p) {
        unsigned char c = (unsigned char)*p;
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void) {
    printf("%d\n", all_unique("abc"));
    printf("%d\n", all_unique("abca"));
    printf("%d\n", all_unique(""));
    printf("%d\n", all_unique(NULL));

    return 0;
}