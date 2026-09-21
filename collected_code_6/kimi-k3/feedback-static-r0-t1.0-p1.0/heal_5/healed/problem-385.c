#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    long long a = 3, b = 0, c = 2;
    long long result = 0;
    
    for (int i = 3; i <= n; i++) {
        result = a + b;
        a = b;
        b = c;
        c = result;
    }
    
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;
    char *endptr;
    long long_input;
    int n;

    read = getline(&buffer, &buffer_size, stdin);
    if (read == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    long_input = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (long_input < 0 || long_input > INT_MAX) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    n = (int)long_input;

    printf("%lld\n", perrin(n));
    free(buffer);
    return EXIT_SUCCESS;
}