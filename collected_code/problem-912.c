#include <stdio.h>
#include <math.h>

// Function to calculate the mth lobb number
double lobbNumber(int m) {
    if (m == 0)
        return 1;
    else if (m == 1)
        return -1;
    else {
        double result = ((2 * m - 1) * lobbNumber(m - 1) - (m - 1) * lobbNumber(m - 2)) / m;
        return result;
    }
}

int main() {
    int m;
    printf("Enter the value of m: ");
    scanf("%d", &m);

    double lobb = lobbNumber(m);
    printf("Lobb number for m = %d is: %.2lf", m, lobb);

    return 0;
}