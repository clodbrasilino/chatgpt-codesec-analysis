#include <stdio.h>
#include <stdlib.h>

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    if (n == 0)
        return 0;
    
    unsigned long long count = 0;
    int i = 0;
    
    while ((1ULL << i) <= n) {
        unsigned long long power = 1ULL << i;
        unsigned long long total_pairs = (n + 1) / (power * 2);
        unsigned long long remainder = (n + 1) % (power * 2);
        
        count += (total_pairs * power);
        count += (remainder > power) ? (remainder - power) : 0;
        
        i++;
    }
    
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    char *endptr = NULL;
    unsigned long long n = strtoull(argv[1], &endptr, 10);
    
    if (*endptr != '\0') {
        return 1;
    }
    
    printf("%llu\n", count_unset_bits_up_to_n(n));
    
    return 0;
}