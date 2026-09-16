#include <stdio.h>
#include <math.h>

void findPerfectSquares(int start, int end) {
    int i;
    int root;
    
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
    
    if (start < 0) {
        start = 0;
    }
    
    root = (int)sqrt(start);
    if (root * root < start) {
        root++;
    }
    
    printf("Perfect squares between %d and %d:\n", start, end);
    
    for (i = root; i * i <= end; i++) {
        printf("%d ", i * i);
    }
    printf("\n");
}

int main(void) {
    int start, end;
    
    printf("Enter two numbers: ");
    if (scanf("%d %d", &start, &end) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    findPerfectSquares(start, end);
    
    return 0;
}