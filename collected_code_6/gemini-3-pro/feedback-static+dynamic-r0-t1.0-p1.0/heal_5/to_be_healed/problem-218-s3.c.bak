#include <stdio.h>
#include <stdlib.h>

int min_operations(int num1, int num2) {
    int steps = 0;
    while (num2 > num1) {
        if (num2 % 2 != 0) {
            num2++;
        } else {
            num2 /= 2;
        }
        steps++;
    }
    return steps + (num1 - num2);
}

/* Possible weaknesses found:
 *  to match this '{'
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 */
int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  expected ';' at end of declaration
     *  expected expression
     *  expected declaration or statement at end of input
     *  expected expression at end of input
     *  expected '}'
     */
    int steps =