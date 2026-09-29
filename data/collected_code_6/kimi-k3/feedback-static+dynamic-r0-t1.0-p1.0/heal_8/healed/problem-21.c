#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

void find_multiples(int n, int m) {
    int i;
    for (i = 1; i <= m; i++) {
        long long result = (long long)n * i;
        if (printf("%lld ", result) < 0) {
            exit(EXIT_FAILURE);
        }
    }
    if (printf("\n") < 0) {
        exit(EXIT_FAILURE);
    }
}

int read_int(const char *prompt, int *out) {
    char buffer[256];
    char *endptr;
    long val;
    size_t len;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 0;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (!feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return 0;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    *out = (int)val;
    return 1;
}

int main(void) {
    int n, m;

    if (!read_int("Enter the number (n): ", &n)) {
        return EXIT_FAILURE;
    }

    if (!read_int("Enter the number of multiples (m): ", &m)) {
        return EXIT_FAILURE;
    }

    if (m <= 0) {
        fprintf(stderr, "m must be positive\n");
        return EXIT_FAILURE;
    }

    find_multiples(n, m);

    return EXIT_SUCCESS;
}