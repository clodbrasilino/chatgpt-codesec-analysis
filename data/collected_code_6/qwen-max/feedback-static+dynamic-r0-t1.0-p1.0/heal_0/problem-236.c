#include <stdio.h>
#include <stdlib.h>

int count_triangles(int n) {
    if (n <= 0) return 0;
    int count = 0, level = n;
    while (level > 0) {
        count += (level * (level + 1)) / 2;
        --level;
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
    int result = count_triangles(n);
    printf("Number of equilateral triangles: %d\n", result);
    return 0;
}