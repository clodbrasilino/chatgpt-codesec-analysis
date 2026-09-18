#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t count_triangles(int n) {
    if (n <= 0) return 0;
    int64_t count = 0;
    for (int level = n; level > 0; --level) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9185183327481608911 + 98765391234572128 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:741,execs:332,op:havoc,rep:8)
         */
        count += (int64_t)level * (level + 1) / 2;
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
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Number of equilateral triangles: %lld\n", result);
    return 0;
}