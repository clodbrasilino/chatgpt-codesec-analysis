#include <stdio.h>

int countSquares(int length, int breadth) {
    if(length > 0 && breadth > 0) {
        int min = (length < breadth) ? length : breadth;
        int max = (length > breadth) ? length : breadth;
        int numSquares = 0;
  
        for (int i = min; i > 0; i--) {
            numSquares += max / i;
            max %= i;
            
            if (max < i) {
                int temp = max;
                max = i;
                i = temp;
            }
        }
        return numSquares;
    }else{
        printf("Input dimensions should be greater than zero.");
        return -1;
    }
}

int main() {
    int length = 15;
    int breadth = 10;

    int result = countSquares(length, breadth);

    if(result != -1) {
        printf("The number of squares in a rectangle with length %d and breadth %d is %d.\n", length, breadth, result);
    }

    return 0;
}