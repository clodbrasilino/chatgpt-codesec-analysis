#include <stdio.h>

int gcd(int a, int b)
{
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void lcm_in_range(int start, int end)
{
    for (int i = start; i <= end; i++) {
        for (int j = i + 1; j <= end; j++) {
            if ((i * j) / gcd(i, j) <= end) {
                printf("Two numbers are: %d and %d\n", i, j);
                return;
            }
        }
    }
    printf("No two distinct numbers found\n");
}

int main()
{
    int start, end;
    printf("Enter the start of the range: ");
    scanf("%d", &start);
    printf("Enter the end of the range: ");
    scanf("%d", &end);

    if (start >= end || start < 0 || end < 0) {
        printf("Invalid range\n");
        return 1;
    }
    
    lcm_in_range(start, end);
    return 0;
}