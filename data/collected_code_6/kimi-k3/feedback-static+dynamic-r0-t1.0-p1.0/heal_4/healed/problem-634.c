#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

uint64_t sum_fourth_power_even(uint32_t n) {
    uint64_t sum = 0;
    uint32_t i;
    for (i = 1; i <= n; i++) {
        uint64_t even_num = (uint64_t)2 * i;
        uint64_t fourth_power = even_num * even_num * even_num * even_num;
        sum += fourth_power;
    }
    return sum;
}

int main(void) {
    uint32_t n;
    char buffer[32];
    char *endptr;
    unsigned long temp;
    
    printf("Enter the value of n: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    errno = 0;
    temp = strtoul(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0') || temp > UINT32_MAX) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    n = (uint32_t)temp;
    
    printf("Sum of fourth power of first %" PRIu32 " even natural numbers: %" PRIu64 "\n", 
           n, sum_fourth_power_even(n));
    
    return 0;
}