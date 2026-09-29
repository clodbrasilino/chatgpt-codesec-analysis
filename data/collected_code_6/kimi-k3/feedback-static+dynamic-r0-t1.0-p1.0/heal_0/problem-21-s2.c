#include <stdio.h>
#include <stdlib.h>

void findMultiples(int n, int m)
{
    int i;
    for (i = 1; i <= m; i++) {
        printf("%d ", n * i);
    }
    printf("\n");
}

int main(void)
{
    int n, m;
    printf("Enter the number (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Enter the count of multiples (m): ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (m <= 0) {
        fprintf(stderr, "m must be positive\n");
        return EXIT_FAILURE;
    }
    findMultiples(n, m);
    return EXIT_SUCCESS;
}