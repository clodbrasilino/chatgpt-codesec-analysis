#include <stdio.h>
#include <math.h>

int countPointsInCircle(int r) {
    int count = 0;
    for (int x = -r; x <= r; x++) {
        for (int y = -r; y <= r; y++) {
            if (x*x + y*y <= r*r) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int r;
    printf("Enter the radius of the circle: ");
    scanf("%d", &r);
    int count = countPointsInCircle(r);
    printf("The number of integer points in the circle is: %d\n", count);
    return 0;
}