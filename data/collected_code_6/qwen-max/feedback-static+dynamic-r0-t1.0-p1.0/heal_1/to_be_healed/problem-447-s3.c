#include <stdio.h>
#include <stdlib.h>

void find_cubes(int *list, int n) {
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9072144 * 3012 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:24371,execs:370,op:havoc,rep:5)
         */
        list[i] = list[i] * list[i] * list[i];
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:8392,execs:182,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        fprintf(stderr, "Number of elements must be positive.\n");
        return 1;
    }

    int *list = (int *)malloc(n * sizeof(int));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }

    find_cubes(list, n);

    printf("Cubes of the elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}