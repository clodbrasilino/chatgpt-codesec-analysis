#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrange(const char *str) {
    int count[26] = {0};
    int n = 0;
    while (str[n] != '\0' && str[n] >= 'a' && str[n] <= 'z') {
        count[str[n] - 'a']++;
        n++;
    }

    if (n == 1) return true;

    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    if (max_count > (n + 1) / 2) {
        return false;
    }

    return true;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "abacaba";
    if (canRearrange(str)) {
        printf("The letters can be rearranged.\n");
    } else {
        printf("The letters cannot be rearranged.\n");
    }

    return 0;
}