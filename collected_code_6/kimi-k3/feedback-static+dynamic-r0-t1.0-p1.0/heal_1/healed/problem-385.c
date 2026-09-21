#include <stdio.h>
#include <stdlib.h>

long long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    long long a = 3, b = 0, c = 2;
    long long result = 0;
    
    for (int i = 3; i <= n; i++) {
        result = a + b;
        a = b;
        b = c;
        c = result;
    }
    
    return result;
}

int main(void) {
    int n;
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (sscanf(buffer, "%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", perrin(n));
    return EXIT_SUCCESS;
}