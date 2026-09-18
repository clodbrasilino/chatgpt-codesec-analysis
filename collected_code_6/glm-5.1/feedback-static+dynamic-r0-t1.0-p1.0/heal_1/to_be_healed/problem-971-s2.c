#include <stdio.h>
#include <stdlib.h>

int find_max_segments(int n, int a, int b, int c) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    int res_a = find_max_segments(n - a, a, b, c);
    int res_b = find_max_segments(n - b, a, b, c);
    int res_c = find_max_segments(n - c, a, b, c);

    int max_res = res_a;
    if (res_b > max_res) {
        max_res = res_b;
    }
    if (res_c > max_res) {
        max_res = res_c;
    }

    if (max_res == -1) {
        return -1;
    }

    return max_res + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:22199,execs:668,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n, a, b, c;
    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        return EXIT_FAILURE;
    }

    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return EXIT_FAILURE;
    }

    int result = find_max_segments(n, a, b, c);
    if (result == -1) {
        printf("0\n");
    } else {
        printf("%d\n", result);
    }

    return EXIT_SUCCESS;
}