#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len + 1);
    if (temp == NULL) {
        return -1;
    }

    memcpy(temp, str, len);
    memcpy(temp + len, str, len);
    temp[2 * len] = '\0';

    int min_rotations = (int)len;
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(str, temp + i, len) == 0) {
            min_rotations = (int)i;
            break;
        }
    }

    free(temp);
    return min_rotations;
}

int main(void) {
    const char *test_str = "abcabc";
    int rotations = find_min_rotations(test_str);
    
    if (rotations != -1) {
        printf("%d\n", rotations);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}