#include <stdio.h>

long long waysOfPainting(int n, int k) {
    if (n < 2)
        return k*n;
    else {
        long long same = k;
        long long diff = k*(k-1);
        for (int i=2; i<n; i++) {
            long long temp = diff;
            diff = (same+diff)*(k-1);
            same = temp;
        }
        return same + diff;
    }
}

int main(void) {
    int n, k;
    printf("Enter the number of posts: ");
    scanf("%d", &n);
    printf("Enter the number of colors: ");
    scanf("%d", &k);
    printf("The number of ways of painting the fence: %lld\n", waysOfPainting(n, k));
    return 0;
}