#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t count_triangles(int n) {
    if (n <= 0) return 0;
    int64_t count = 0;
    for (int level = n; level > 0; --level) {
        int64_t temp = (int64_t)level * (level + 1) / 2;
        if (__builtin_add_overflow(count, temp, &count)) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
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
    printf("Number of equilateral triangles: %" PRId64 "\n", result);
    return 0;
}