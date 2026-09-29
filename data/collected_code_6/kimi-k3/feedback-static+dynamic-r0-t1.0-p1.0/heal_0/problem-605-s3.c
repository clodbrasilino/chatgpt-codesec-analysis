#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    if (num == 2) {
        return true;
    }
    if (num % 2 == 0) {
        return false;
    }
    
    for (int i = 3; i <= num / i; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int num;
    char buffer[256];
    
    printf("Enter an integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    if (sscanf(buffer, "%d", &num) != 1) {
        fprintf(stderr, "Invalid input format\n");
        return 1;
    }
    
    if (is_prime(num)) {
        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }
    
    return 0;
}