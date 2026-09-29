#include <stdio.h>
#include <stdlib.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len + 1);
    if (temp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        temp[i] = str[i];
        temp[i + len] = str[i];
    }
    temp[2 * len] = '\0';

    int min_rotations = (int)len;
    for (size_t i = 1; i <= len; i++) {
        int match = 1;
        for (size_t j = 0; j < len; j++) {
            if (str[j] != temp[i + j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            min_rotations = (int)i;
            break;
        }
    }

    free(temp);
    return min_rotations;
}

int main(void) {
    char str[4096];
    if (scanf("%4095s", str) == 1) {
        int rotations = find_min_rotations(str);
        if (rotations != -1) {
            printf("%d\n", rotations);
        }
    }
    return 0;
}