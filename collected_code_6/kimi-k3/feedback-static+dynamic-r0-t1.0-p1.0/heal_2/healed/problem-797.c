#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

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
    
    char buffer[64];
    int pos = 0;
    
    while (value > 0 && pos < (int)sizeof(buffer)) {
        buffer[pos++] = '0' + (int)(value % 10);
        value /= 10;
    }
    
    for (int i = pos - 1; i >= 0; i--) {
        printf("%c", buffer[i]);
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