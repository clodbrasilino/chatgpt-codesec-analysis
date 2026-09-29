#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_flips_to_alternate(const char *str, size_t len) {
    int flips_start0 = 0;
    int flips_start1 = 0;

    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != '0') flips_start0++;
            if (str[i] != '1') flips_start1++;
        } else {
            if (str[i] != '1') flips_start0++;
            if (str[i] != '0') flips_start1++;
        }
    }

    return flips_start0 < flips_start1 ? flips_start0 : flips_start1;
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    printf("Enter binary string: ");
    nread = getline(&input, &bufsize, stdin);
    if (nread == -1) {
        free(input);
        return 1;
    }

    size_t len = (size_t)nread;
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("0\n");
        free(input);
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            fprintf(stderr, "Invalid input: only '0' and '1' allowed\n");
            free(input);
            return 1;
        }
    }

    int result = min_flips_to_alternate(input, len);
    printf("%d\n", result);

    free(input);
    return 0;
}