#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrange(char *str, size_t len) {
    int count[26] = {0};

    for (int i = 0; i < len; i++) {
        count[str[i] - 'a']++;
    }

    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    if (max_count > (len + 1) / 2) {
        return false;
    }

    return true;
}

int main() {
    char str[] = "abacaba";
    size_t len = sizeof(str) / sizeof(str[0]) - 1;

    if (canRearrange(str, len)) {
        printf("The letters can be rearranged.\n");
    } else {
        printf("The letters cannot be rearranged.\n");
    }

    return 0;
}