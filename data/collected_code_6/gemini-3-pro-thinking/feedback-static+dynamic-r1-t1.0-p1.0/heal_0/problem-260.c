#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

typedef enum {
    NSW_SUCCESS = 0,
    NSW_ERR_INVALID_INPUT,
    NSW_ERR_OVERFLOW
} nsw_error_t;

bool is_prime(uint64_t n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (uint64_t i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

nsw_error_t find_nth_nsw_prime(unsigned int n, uint64_t *result) {
    if (n == 0 || result == NULL) {
        return NSW_ERR_INVALID_INPUT;
    }

    uint64_t prev = 1;
    uint64_t curr = 7;
    unsigned int count = 0;

    if (is_prime(curr)) {
        count++;
        if (count == n) {
            *result = curr;
            return NSW_SUCCESS;
        }
    }

    while (1) {
        if (curr > UINT64_MAX / 6) {
            return NSW_ERR_OVERFLOW;
        }
        
        uint64_t next = 6 * curr - prev;
        prev = curr;
        curr = next;

        if (is_prime(curr)) {
            count++;
            if (count == n) {
                *result = curr;
                return NSW_SUCCESS;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr = NULL;
    long n_signed = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || n_signed <= 0 || n_signed > INT_MAX) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)n_signed;
    uint64_t result = 0;
    nsw_error_t status = find_nth_nsw_prime(n, &result);

    if (status == NSW_SUCCESS) {
        printf("%" PRIu64 "\n", result);
    } else if (status == NSW_ERR_OVERFLOW) {
        fprintf(stderr, "Error: The requested NSW prime exceeds the maximum capacity of a 64-bit unsigned integer.\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Error: Invalid parameters provided to the computation function.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}