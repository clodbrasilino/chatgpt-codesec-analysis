#include <stdio.h>
#include <stdlib.h>

long long find_carol_number(int n, int *error) {
    if (n <= 0 || n > 31) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }
    
    if (error != NULL) {
        *error = 0;
    }
    
    long long power_of_two = 1LL << n;
    long long term = power_of_two - 1LL;
    
    return (term * term) - 2LL;
}

int main(void) {
    int n = 4;
    int error = 0;
    long long carol;

    carol = find_carol_number(n, &error);

    if (error != 0) {
        fprintf(stderr, "Invalid input for Carol number calculation.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", carol);

    return EXIT_SUCCESS;
}