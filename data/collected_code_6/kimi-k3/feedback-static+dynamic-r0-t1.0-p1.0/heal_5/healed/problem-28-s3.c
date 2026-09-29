#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

uint64_t binomial_coefficient(uint64_t n, uint64_t k)
{
    uint64_t result = 1;
    uint64_t i;

    if (k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (i = 0; i < k; ++i) {
        if (result != 0 && (n - i) > UINT64_MAX / result) {
            return 0;
        }
        result = result * (n - i) / (i + 1);
    }

    return result;
}

int main(void)
{
    uint64_t n, k, result;
    char input_buffer[256];
    char *endptr;
    char *current_pos;
    unsigned long long temp_n, temp_k;

    printf("Enter n and k: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (strchr(input_buffer, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    temp_n = strtoull(input_buffer, &endptr, 10);
    if (errno == ERANGE || endptr == input_buffer) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    current_pos = endptr;
    while (*current_pos == ' ' || *current_pos == '\t') {
        current_pos++;
    }
    
    errno = 0;
    char *k_endptr;
    temp_k = strtoull(current_pos, &k_endptr, 10);
    if (errno == ERANGE || k_endptr == current_pos) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    while (*k_endptr == ' ' || *k_endptr == '\t') {
        k_endptr++;
    }
    
    if (*k_endptr != '\n' && *k_endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (temp_n > UINT64_MAX || temp_k > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    n = (uint64_t)temp_n;
    k = (uint64_t)temp_k;

    result = binomial_coefficient(n, k);
    printf("C(%" PRIu64 ", %" PRIu64 ") = %" PRIu64 "\n", n, k, result);

    return 0;
}