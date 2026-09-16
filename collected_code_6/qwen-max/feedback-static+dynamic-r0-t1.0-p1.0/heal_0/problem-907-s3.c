#include <stdio.h>
#include <stdlib.h>

void sieve(int *l, int n) {
    for (int i = 1; i < n; ++i) {
        if (l[i] != -1) {
            int step = l[i];
            for (int j = i + 2 * step; j < n; j += step) {
                while (l[j] == -1) j += step;
                l[j] = -1;
            }
            int k = i + step;
            while (k < n && l[k] == -1) k += step;
            if (k < n) l[i] = l[k];
            else l[i] = -1;
        }
    }
}

void print_lucky_numbers(int n) {
    if (n <= 0) return;
    int *is_lucky = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) is_lucky[i] = 2 * i - 1;
    is_lucky[0] = -1;

    sieve(is_lucky, n + 1);

    for (int i = 1, count = 0; count < n; ++i) {
        if (is_lucky[i] != -1) {
            printf("%d ", is_lucky[i]);
            ++count;
        }
    }
    printf("\n");
    free(is_lucky);
}

int main() {
    int n;
    scanf("%d", &n);
    print_lucky_numbers(n);
    return 0;
}