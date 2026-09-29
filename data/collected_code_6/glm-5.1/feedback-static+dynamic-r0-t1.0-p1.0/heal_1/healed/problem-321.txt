#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *find_demlo_number(int n) {
    const char *pattern_str = "123456789";

    if (n < 1 || n > 9) {
        errno = ERANGE;
        return NULL;
    }

    size_t total_len = n * 2 - 1;
    char *result = malloc(total_len + 1);
    if (!result) {
        errno = ENOMEM;
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        result[i] = pattern_str[i];
    }
    for (int i = n - 2; i >= 0; i--) {
        result[n + (n - 2 - i)] = pattern_str[i];
    }
    
    result[total_len] = '\0';
    return result;
}

int main(void) {
    int n = 5;
    char *demlo = find_demlo_number(n);
    
    if (demlo) {
        printf("%d: %s\n", n, demlo);
        free(demlo);
        demlo = NULL;
    } else {
        if (errno == ERANGE) {
            fprintf(stderr, "Input out of valid range [1, 9]\n");
        } else if (errno == ENOMEM) {
            fprintf(stderr, "Memory allocation failed\n");
        } else {
            fprintf(stderr, "Unknown error\n");
        }
        return 1;
    }
    
    return 0;
}