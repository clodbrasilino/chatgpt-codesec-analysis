#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

int find_smallest_triangular_index(int n) {
    if (n > 16) return INT_MAX; // Prevent overflow and invalid results for large n
    double lower_bound = pow(10, (n-1));
    double term = 1 + 8 * lower_bound;
    if (term >= DBL_MAX) return INT_MAX; // Check for potential overflow before sqrt
    double root = (sqrt(term) - 1) / 2;
    if (root > INT_MAX) return INT_MAX; // Ensure the result is within the range of int
    return (int)ceil(root);
}

int main() {
    int n;
    printf("Enter the number of digits: ");
    scanf("%d", &n);
    if (n <= 0) {
        return 1;
    }
    int index = find_smallest_triangular_index(n);
    if (index == INT_MAX) {
        printf("The index cannot be calculated for this number of digits.\n");
    } else {
        printf("The index of the smallest triangular number with %d digits is: %d\n", n, index);
    }
    return 0;
}