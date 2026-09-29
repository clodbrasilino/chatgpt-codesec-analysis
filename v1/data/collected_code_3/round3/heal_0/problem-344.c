#include <stdio.h>
#include <math.h>

int countOddFactors(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        int root = sqrt(i);
        if (root * root == i) {
            count++;
        }
    }
    return count;
}

int main() {
    int start, end;
    printf("Enter the start of the range: ");
    scanf("%d", &start);
    printf("Enter the end of the range: ");
    scanf("%d", &end);
    int count = countOddFactors(start, end);
    printf("Number of elements with odd factors in the given range: %d\n", count);
    return 0;
}