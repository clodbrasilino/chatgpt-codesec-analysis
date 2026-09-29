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

    len = strlen(str);
    if (len == 0) {
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

    strcpy(concatenated, str);
    strcat(concatenated, str);

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
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
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