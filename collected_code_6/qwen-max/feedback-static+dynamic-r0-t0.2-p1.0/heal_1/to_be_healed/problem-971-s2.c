#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 * ASan: stack-overflow (AFL crash: id:000001,sig:11,src:000001,time:216,execs:114,op:arith8,pos:5,val:+35)
 */
int max_segments(int n, int a, int b, int c) {
    if (n < 0) return -1;
    if (n == 0) return 0;

    int max = -1;
    int result;

    result = max_segments(n - a, a, b, c);
    if (result != -1 && result + 1 > max) max = result + 1;

    result = max_segments(n - b, a, b, c);
    if (result != -1 && result + 1 > max) max = result + 1;

    result = max_segments(n - c, a, b, c);
    if (result != -1 && result + 1 > max) max = result + 1;

    return max;
}

int main() {
    int n, a, b, c;
    printf("Enter the total length n: ");
    scanf("%d", &n);
    printf("Enter the segment lengths a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);

    int result = max_segments(n, a, b, c);
    if (result == -1) {
        printf("No segments can be formed.\n");
    } else {
        printf("Maximum number of segments: %d\n", result);
    }

    return 0;
}