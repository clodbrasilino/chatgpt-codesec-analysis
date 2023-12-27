#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    int i;
    
    for(i = start; i <= end; i++) {
        int squareRoot = sqrt(i);
        
        if (squareRoot * squareRoot == i) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int start, end;
    
    printf("Enter the start number: ");
    scanf("%d", &start);
    printf("Enter the end number: ");
    scanf("%d", &end);
    
    printf("Perfect squares between %d and %d are:\n", start, end);
    findPerfectSquares(start, end);
    
    return 0;
}