#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char first_non_repeated_char(const char *str) {
    unsigned int count[UCHAR_MAX + 1];
    int first_pos[UCHAR_MAX + 1];
    size_t i;

    if (str == NULL) {
        return '\0';
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        count[i] = 0;
        first_pos[i] = -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] < UINT_MAX) {
            count[c]++;
        }
        if (first_pos[c] == -1) {
            first_pos[c] = (int)i;
        }
    }

    int min_pos = INT_MAX;
    for (i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] == 1 && first_pos[i] < min_pos) {
            min_pos = first_pos[i];
        }
    }

    if (min_pos != INT_MAX && min_pos >= 0) {
        return (char)str[min_pos];
    }

    return '\0';
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    printf("Enter a string: ");
    nread = getline(&input, &bufsize, stdin);
    if (nread == -1) {
        free(input);
        return 1;
    }

    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
        nread--;
    }

    if (nread > 0) {
        char result = first_non_repeated_char(input);

        if (result != '\0') {
            printf("First non-repeated character: %c\n", result);
        } else {
            printf("No non-repeated character found.\n");
        }
    } else {
        printf("No non-repeated character found.\n");
    }

    free(input);
    return 0;
}