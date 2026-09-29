#include <stdio.h>
#include <stdlib.h>

int nth_ap_term(int first_term, int common_difference, int n) {
    if (n <= 0) {
        fprintf(stderr, "Error: Term position must be positive\n");
        exit(EXIT_FAILURE);
    }
    
    return first_term + (n - 1) * common_difference;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000006,time:13890,execs:4798,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int first_term, common_difference, n, result;
    
    printf("Enter first term: ");
    if (scanf("%d", &first_term) != 1) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%d", &common_difference) != 1) {
        fprintf(stderr, "Error: Invalid input for common difference\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter term position (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input for term position\n");
        return EXIT_FAILURE;
    }
    
    result = nth_ap_term(first_term, common_difference, n);
    
    printf("The %dth term is: %d\n", n, result);
    
    return EXIT_SUCCESS;
}