#include <stdio.h>
#include <stdint.h>
#include <limits.h>

static int count_set_bits(uint64_t value)
{
    int count = 0;
    
    while (value != 0U) {
        count += (int)(value & 1U);
        value >>= 1U;
    }
    
    return count;
}

static int count_integers_with_odd_set_bits(uint64_t start, uint64_t end, uint64_t *result)
{
    uint64_t i;
    uint64_t count = 0;
    
    if (result == NULL) {
        return -1;
    }
    
    if (start > end) {
        return -1;
    }
    
    for (i = start; i <= end; i++) {
        int bit_count = count_set_bits(i);
        
        if ((bit_count % 2) != 0) {
            count++;
        }
        
        if (i == UINT64_MAX) {
            break;
        }
    }
    
    *result = count;
    return 0;
}

int main(void)
{
    uint64_t start = 0;
    uint64_t end = 100;
    uint64_t result = 0;
    int status;
    
    status = count_integers_with_odd_set_bits(start, end, &result);
    
    if (status != 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return 1;
    }
    
    printf("Number of integers with odd set bits in range [%llu, %llu]: %llu\n",
           (unsigned long long)start,
           (unsigned long long)end,
           (unsigned long long)result);
    
    return 0;
}