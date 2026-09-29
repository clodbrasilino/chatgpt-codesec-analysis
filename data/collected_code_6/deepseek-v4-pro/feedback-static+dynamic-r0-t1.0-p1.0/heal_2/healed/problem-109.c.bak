#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *s) {
    int n = strlen(s);
    if (n == 0) {
        return 0;
    }

    int *doubled = (int *)malloc(2 * n * sizeof(int));
    if (doubled == NULL) {
        return -1;
    }

    for (int i = 0; i < 2 * n; i++) {
        doubled[i] = s[i % n] - '0';
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (doubled[i + n - 1] & 1) {
            int valid = 1;
            for (int j = 0; j < n && j < 30; j++) {
                if (doubled[i + j] != 0 && doubled[i + j] != 1) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                count++;
            }
        }
    }

    free(doubled);
    return count;
}

int main(void) {
    char input[256];
    if (scanf("%255s", input) != 1) {
        return 1;
    }

    int result = count_odd_rotations(input);
    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}