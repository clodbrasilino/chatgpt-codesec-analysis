#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_odd_factors(int low, int high) {
    int low_sqrt = (int)ceil(sqrt((double)low));
    int high_sqrt = (int)floor(sqrt((double)high));
    
    if (high_sqrt < low_sqrt) {
        return 0;
    }
    
    return high_sqrt - low_sqrt + 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <low> <high>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 1 || val2 < 1 || val1 > val2) {
        fprintf(stderr, "Invalid range. Provide positive integers where low <= high.\n");
        return EXIT_FAILURE;
    }
    
    int result = count_odd_factors((int)val1, (int)val2);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}