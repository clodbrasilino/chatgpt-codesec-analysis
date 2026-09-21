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
    size_t buffer_size = 4096;
    char *str = (char *)malloc(buffer_size);
    if (str == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(str, (int)buffer_size, stdin) != NULL) {
        str[strcspn(str, "\r\n")] = '\0';
        
        int rotations = find_min_rotations(str);
        if (rotations != -1) {
            printf("%d\n", rotations);
        }
    }

    free(str);
    return EXIT_SUCCESS;
}