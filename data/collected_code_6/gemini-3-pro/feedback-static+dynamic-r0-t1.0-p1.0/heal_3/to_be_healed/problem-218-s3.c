#include <stdio.h>
#include <stdlib.h>

int min_operations(int num1, int num2) {
    int diff = abs(num1 - num2);
    int ops = 0;
    
    if (diff == 0) return 0;
    
    ops += diff / 10;
    diff %= 10;
    
    ops += diff / 5;
    diff %= 5;
    
    ops += diff / 2;
    diff %= 2;
    
    ops += diff;
    
    return ops;
}

/* Possible weaknesses found:
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  to match this '{'
 */
int main(void) {
    /* Possible weaknesses found:
     *  expected '}'
     *  expected declaration or statement at end of input
     */
    int num1, num2;