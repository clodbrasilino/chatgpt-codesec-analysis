#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int minSwapsToEqual(const char *a, const char *b, size_t len) {
    int count01 = 0, count10 = 0;
    for (size_t i = 0; i < len; i++) {
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
    char a[100], b[100];
    size_t len_a, len_b;

    if (scanf("%99s", a) != 1 || scanf("%99s", b) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    if (len_a != len_b) {
        printf("Strings are of different lengths.\n");
        return 1;
    }

    int result = minSwapsToEqual(a, b, len_a);

    if (result == -1) {
        printf("Strings cannot be made equal by swapping\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}