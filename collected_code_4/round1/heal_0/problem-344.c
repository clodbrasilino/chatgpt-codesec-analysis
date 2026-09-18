#include <stdio.h>
#include <math.h>

int countOddFactors(int start, int end) {
    int count = 0;
    for(int i = start; i <= end; i++) {
        int root = sqrt(i);
        if(root * root == i) {
            count++;
        }
    }
    return count;
}

int main() {
    int start, end;
    printf("Enter the start of the range:");
    scanf("%d", &start);
    printf("Enter the end of the range:");
    scanf("%d", &end);
    if(start > end) {
        printf("Invalid Range.\n");
        return 0;
    } else {
        printf("Number of elements with odd factors: %d\n", countOddFactors(start, end));
    }
    return 0;
}