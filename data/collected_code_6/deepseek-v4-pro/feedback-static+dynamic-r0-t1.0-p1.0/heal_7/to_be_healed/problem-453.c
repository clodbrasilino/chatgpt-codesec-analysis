#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_even_factors(int64_t n) {
    if (n <= 0) return 0;
    if (n % 2 != 0) return 0;

    int64_t sum = 0;
    int64_t temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    if (temp != 1) {
        sum += 2;
    }

    int64_t limit = (int64_t)sqrt((double)n);
    for (int64_t i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            if (i % 2 == 0) sum += i;
            int64_t counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) sum += counterpart;
        }
    }

    if (n != 2) sum += n;
    return sum;
}

int main(void) {
    int64_t number;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[64];

    printf("Enter a number: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input_buffer, "%" SCNd64, &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Sum of even factors: %" PRId64 "\n", sum_even_factors(number));
    return 0;
}