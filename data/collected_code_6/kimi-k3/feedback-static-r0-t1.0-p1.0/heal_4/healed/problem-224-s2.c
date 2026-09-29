#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

unsigned int count_set_bits(uint32_t number) {
    unsigned int count = 0;
    while (number != 0) {
        number &= (number - 1);
        count++;
    }
    return count;
}

int main(void) {
    uint32_t input;
    char buffer[64];
    char *endptr;
    unsigned long value;
    
    printf("Enter a number: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (buffer[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    value = strtoul(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0' || value > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    input = (uint32_t)value;
    
    printf("Number of set bits: %u\n", count_set_bits(input));
    
    return 0;
}