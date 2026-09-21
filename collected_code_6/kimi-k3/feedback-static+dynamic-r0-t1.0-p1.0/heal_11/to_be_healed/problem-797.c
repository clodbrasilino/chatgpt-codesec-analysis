#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

__int128 sum_odd_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    __int128 first_odd = (l % 2 == 0) ? (__int128)l + 1 : (__int128)l;
    
    if (first_odd > (__int128)r) {
        return 0;
    }
    
    __int128 last_odd = (r % 2 == 0) ? (__int128)r - 1 : (__int128)r;
    __int128 count = (last_odd - first_odd) / 2 + 1;
    
    return count * (first_odd + last_odd) / 2;
}

void print_int128(__int128 value) {
    if (value == 0) {
        printf("0");
        return;
    }
    
    if (value < 0) {
        printf("-");
        value = -value;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    size_t pos = 0;
    size_t buffer_size = sizeof(buffer);
    
    while (value > 0 && pos < buffer_size - 1) {
        buffer[pos++] = (char)('0' + (int)(value % 10));
        value /= 10;
    }
    
    for (size_t i = pos; i > 0; i--) {
        printf("%c", buffer[i - 1]);
    }
}

int main(void) {
    long long l, r;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    
    __int128 result = sum_odd_natural_numbers(l, r);
    print_int128(result);
    printf("\n");
    
    return EXIT_SUCCESS;
}