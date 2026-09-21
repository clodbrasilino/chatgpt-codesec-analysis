#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int64_t maxVolume(int64_t S) {
    if (S < 3) {
        return 0;
    }
    
    int64_t a = S / 3;
    int64_t b = (S - a) / 2;
    int64_t c = S - a - b;
    
    if (a < 1 || b < 1 || c < 1) {
        return 0;
    }
    
    if (b > INT64_MAX / a) {
        return 0;
    }
    
    int64_t ab = a * b;
    
    if (c > INT64_MAX / ab) {
        return 0;
    }
    
    return ab * c;
}

int main(void) {
    int64_t sumSides;
    char buffer[64];
    char *endptr;
    size_t len;
    
    printf("Enter sum of sides: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    errno = 0;
    sumSides = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Value out of range\n");
        return 1;
    }
    
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (sumSides < 3 || sumSides > INT64_MAX) {
        fprintf(stderr, "Sum must be at least 3\n");
        return 1;
    }
    
    int64_t volume = maxVolume(sumSides);
    printf("Maximum volume: %" PRId64 "\n", volume);
    
    return 0;
}