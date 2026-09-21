#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

int is_abundant(int64_t n) {
    if (n <= 1) return 0;
    
    if (n > INT64_MAX / 2) return 0;
    
    int64_t sum = 1;
    int64_t sqrt_n = (int64_t)sqrt((double)n);
    
    for (int64_t i = 2; i <= sqrt_n; i++) {
        if (n % i == 0) {
            sum += i;
            int64_t complement = n / i;
            if (i != complement) {
                if (sum > INT64_MAX - complement) {
                    return 1;
                }
                sum += complement;
                if (sum > n) {
                    return 1;
                }
            }
        }
    }
    
    if (sum > n) return 1;
    
    return 0;
}

int main(void) {
    int64_t number;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input, "%31" SCNd64, &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (number <= 0) {
        fprintf(stderr, "Please enter a positive number\n");
        return 1;
    }
    
    if (is_abundant(number)) {
        printf("%" PRId64 " is an abundant number\n", number);
    } else {
        printf("%" PRId64 " is not an abundant number\n", number);
    }
    
    return 0;
}