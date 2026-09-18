#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

int findClosestSmallerNumber(int n) {
    // Depending on the use-case, error handling can be improved.
    /* Possible weaknesses found:
     *  'INT_MIN' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if(n == INT_MIN) {
        printf("No smaller integer exists.\n");
        exit(EXIT_FAILURE);
    } else {
        return n - 1;
    }
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    int closestSmallerNumber = findClosestSmallerNumber(number);
    printf("Closest smaller number than %d is %d.\n", number, closestSmallerNumber);
    return 0;
}