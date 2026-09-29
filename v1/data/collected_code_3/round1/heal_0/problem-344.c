#include <stdio.h>
#include <math.h>

int oddFactors(int start, int end) {
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
    printf("Enter start of range: ");
    scanf("%d", &start);
    printf("Enter end of range: ");
    scanf("%d", &end);
    int count = oddFactors(start, end);
    printf("Number of elements with odd factors in range: %d\n", count);
    return 0;
}