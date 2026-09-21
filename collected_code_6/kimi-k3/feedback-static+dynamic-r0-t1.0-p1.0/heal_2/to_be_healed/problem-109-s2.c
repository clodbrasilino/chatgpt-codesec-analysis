#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countOddRotations(const char *str) {
    size_t len;
    size_t i;
    int count = 0;
    char *concatenated;
    size_t start;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, 1024);
    if (len == 0 || len == 1024) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }
    }

    concatenated = (char *)malloc((2 * len + 1) * sizeof(char));
    if (concatenated == NULL) {
        return -1;
    }

    snprintf(concatenated, 2 * len + 1, "%s%s", str, str);

    for (start = 0; start < len; start++) {
        int isOdd = (concatenated[start + len - 1] == '1');
        if (isOdd) {
            count++;
        }
    }

    free(concatenated);
    concatenated = NULL;

    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        int result = countOddRotations(buffer);
        if (result >= 0) {
            printf("%d\n", result);
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}