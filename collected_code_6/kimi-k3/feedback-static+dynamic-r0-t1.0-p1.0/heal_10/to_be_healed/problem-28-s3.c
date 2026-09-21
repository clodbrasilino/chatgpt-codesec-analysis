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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *endptr;
    char *current_pos;
    char *k_endptr;
    unsigned long long temp_n, temp_k;
    size_t input_len;

    printf("Enter n and k: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input_buffer);
    if (input_len == sizeof(input_buffer) - 1 && input_buffer[input_len - 1] != '\n' && !feof(stdin)) {
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