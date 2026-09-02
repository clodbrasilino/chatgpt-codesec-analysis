#include <stdio.h>
#include <math.h>

int find_smallest_triangular_index(int n) {
    double lower_bound = pow(10, (n-1));
    /* Possible weaknesses found:
     *  Variable 'upper_bound' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'upper_bound' during its initialization is never read [deadcode.DeadStores]
     */
    double upper_bound = pow(10, n) - 1;
    double root = (sqrt(1 + 8 * lower_bound) - 1) / 2;
    return ceil(root);
}

int main() {
    int n;
    printf("Enter the number of digits: ");
    scanf("%d", &n);
    if (n <= 0) {
        return 1;
    }
    int index = find_smallest_triangular_index(n);
    printf("The index of the smallest triangular number with %d digits is: %d\n", n, index);
    return 0;
}