#include <stdio.h>
#include <stdlib.h>

void findMultiples(int n, int m) {
    for (int i = 1; i <= m; i++) {
        printf("%d ", i * n);
    }
    printf("\n");
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000005,time:4688,execs:1105,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    findMultiples(n, m);
    return 0;
}