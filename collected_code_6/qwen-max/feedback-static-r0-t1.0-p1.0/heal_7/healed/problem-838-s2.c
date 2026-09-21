#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

int minSwapsToEqual(const char *a, const char *b) {
    int count01 = 0, count10 = 0;
    for (size_t i = 0; a[i] != '\0'; i++) {
        if (a[i] == '0' && b[i] == '1') {
            count01++;
        } else if (a[i] == '1' && b[i] == '0') {
            count10++;
        }
    }
    if ((count01 + count10) % 2 != 0) {
        return -1;
    }
    return (count01 + count10) / 2;
}

int main() {
    char *a = malloc(100 * sizeof(char));
    char *b = malloc(100 * sizeof(char));

    if (!a || !b) {
        printf("Memory allocation failed\n");
        return 1;
    }

    if (scanf("%99s %99s", a, b) != 2) {
        free(a);
        free(b);
        printf("Input error\n");
        return 1;
    }

    if (strlen(a) != strlen(b)) {
        free(a);
        free(b);
        printf("Strings are not of the same length\n");
        return 1;
    }

    int result = minSwapsToEqual(a, b);

    if (result == -1) {
        printf("Strings cannot be made equal by swapping\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    free(a);
    free(b);

    return 0;
}