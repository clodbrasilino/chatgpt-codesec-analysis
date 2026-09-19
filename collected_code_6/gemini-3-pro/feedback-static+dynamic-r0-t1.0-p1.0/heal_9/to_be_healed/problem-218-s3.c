#include <stdio.h>
#include <stdlib.h>

int min_operations(int a, int b) {
    if (a == b) return 0;
    if (a < b) {
        int diff = b - a;
        if (diff % 2 != 0) return 1;
        return 2;
    } else {
        int diff = a - b;
        if (diff % 2 == 0) return 1;
        return 2;
    }
}

/* Possible weaknesses found:
 *  to match this '{'
 */
int main(void) {
    int t;
    /* Possible weaknesses found:
     *  to match this '{'
     */
    if (scanf("%d", &t) == 1) {
        /* Possible weaknesses found:
         *  to match this '{'
         *  expected declaration or statement at end of input
         *  expected '}'
         *  Unmatched '{'. Configuration: ''. [syntaxError]
         */
        while (t-- > 0) {