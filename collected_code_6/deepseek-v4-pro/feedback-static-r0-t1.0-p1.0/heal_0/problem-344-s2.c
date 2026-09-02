#include <stdio.h>
#include <math.h>

int countOddFactors(int left, int right) {
    int count = 0;
    for (int i = left; i <= right; i++) {
        int root = (int)sqrt(i);
        if (root * root == i) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int left, right;
    printf("Enter range (left right): ");
    if (scanf("%d %d", &left, &right) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    if (left > right) {
        int temp = left;
        left = right;
        right = temp;
    }
    if (left < 0) {
        left = 0;
    }
    int result = countOddFactors(left, right);
    printf("Count of numbers with odd factors: %d\n", result);
    return 0;
}