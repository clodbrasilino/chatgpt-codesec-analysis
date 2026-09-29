#include <stdio.h>
#include <stdlib.h>

long long count_squares(int length, int width) {
    if (length <= 0 || width <= 0) {
        return 0;
    }
    
    long long total = 0;
    int min_dim = length < width ? length : width;
    
    for (int size = 1; size <= min_dim; size++) {
        total += (long long)(length - size + 1) * (width - size + 1);
    }
    
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:6917,execs:2883,op:havoc,rep:13; likely memory-safety defect
  */

int main(void) {
    int length, width;
    
    printf("Enter length and width of rectangle: ");
    if (scanf("%d %d", &length, &width) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares(length, width);
    printf("Number of squares: %lld\n", result);
    
    return EXIT_SUCCESS;
}