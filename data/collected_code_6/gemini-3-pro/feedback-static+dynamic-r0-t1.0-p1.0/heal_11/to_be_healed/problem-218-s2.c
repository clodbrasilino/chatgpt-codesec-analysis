#include <stdio.h>
#include <stdlib.h>

long long min_operations(long long a, long long b) {
    long long diff = a > b ? a - b : b - a;
    if (diff == 0) return 0;
    
    long long ans = (diff / 3) * 2;
    long long rem = diff % 3;
    
    if (rem == 1) {
        ans += 1;
    } else if (rem == 2) {
        ans += 3;
    }
    
    return ans;
}

/* Possible weaknesses found:
 *  to match this '{'
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 */
int main(void) {
    int t;
    /* Possible weaknesses found:
     *  expected declaration or statement at end of input
     *  expected expression
     *  to match this '('
     *  expected ')' at end of input
     *  expected '}'
     *  expected ')'
     */
    if (scanf("%d", &t)