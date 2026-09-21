#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int64_t cube_sum(int64_t n)
{
    if (n < 0 || n > 1290) {
        return -1;
    }
    
    int64_t sum = n * (n + 1) / 2;
    return sum * sum;
}

int main(void)
{
    int64_t n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    if (sscanf(buffer, "%" SCNd64 "%c", &n, &endptr) != 1) {
        return 1;
    }
    
    int64_t result = cube_sum(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    return 0;
}