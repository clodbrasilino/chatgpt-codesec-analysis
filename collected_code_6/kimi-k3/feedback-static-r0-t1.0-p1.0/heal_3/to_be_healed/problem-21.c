#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void find_multiples(int n, int m) {
    int i;
    for (i = 1; i <= m; i++) {
        printf("%d ", n * i);
    }
    printf("\n");
}

int main(void) {
    int n, m;
    char *endptr;
    char *buffer;
    size_t buffer_size = 256;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number (n): ");
    read = getline(&buffer, &buffer_size, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    long n_long = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || n_long < INT_MIN || n_long > INT_MAX) {
        fprintf(stderr, "Invalid input for n\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    n = (int)n_long;

    printf("Enter the number of multiples (m): ");
    read = getline(&buffer, &buffer_size, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    long m_long = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\n' || m_long < INT_MIN || m_long > INT_MAX) {
        fprintf(stderr, "Invalid input for m\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    m = (int)m_long;

    free(buffer);

    if (m <= 0) {
        fprintf(stderr, "m must be positive\n");
        return EXIT_FAILURE;
    }

    find_multiples(n, m);

    return EXIT_SUCCESS;
}