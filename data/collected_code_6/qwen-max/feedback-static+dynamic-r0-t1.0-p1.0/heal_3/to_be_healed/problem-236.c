#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t count_triangles(int n) {
    if (n <= 0) return 0;
    int64_t count = 0;
    for (int level = n; level > 0; --level) {
        int64_t temp = (int64_t)level * (level + 1) / 2;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9195056165383843215 + 48395002738289581 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:851,execs:371,op:havoc,rep:7)
         */
        count += temp;
    }
    return count;
}

int main() {
    int n;
    printf("Enter the number of levels: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    int64_t result = count_triangles(n);
    printf("Number of equilateral triangles: %lld\n", (long long)result);
    return 0;
}