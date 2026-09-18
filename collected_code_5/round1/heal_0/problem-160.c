#include <stdio.h>
#include <stdbool.h>

// Structure to hold x, y values pair
typedef struct {
    int x;
    int y;
} Coefficients;

// Function to find x & y 
bool findCoefficients(int a, int b, int n, Coefficients* result) {
    for (int i = 0; i * a <= n; ++i) {
        for (int j = 0; j * b <= n; ++j) {
            if ((i * a + j * b) == n) {
                result->x = i;
                result->y = j;
                return true;
            }
        }
    }
    return false;
}

// Main function
int main() {
    Coefficients result;
    int a = 2, b = 3, n = 7;
    
    if (findCoefficients(a, b, n, &result)) {
        printf("x = %d, y = %d satisfy the equation %dx + %dy = %d\n", result.x, result.y, a, b, n);
    } else {
        printf("No integer solution for x and y found to satisfy the equation %dx + %dy = %d\n", a, b, n);
    }

    return 0;
}