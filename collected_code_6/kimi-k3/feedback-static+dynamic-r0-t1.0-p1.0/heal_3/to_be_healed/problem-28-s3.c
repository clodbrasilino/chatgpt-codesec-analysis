#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

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

    printf("Enter n and k: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input_buffer, "%" SCNu64 " %" SCNu64, &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = binomial_coefficient(n, k);
    printf("C(%" PRIu64 ", %" PRIu64 ") = %" PRIu64 "\n", n, k, result);

    return 0;
}