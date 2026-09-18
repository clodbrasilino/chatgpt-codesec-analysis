#include <stdio.h>

long long int computeWaystoPaintFence(int n, int k) {
    long long int total = k;
    int same = 0, diff = k;

    for(int i = 2; i <= n; i++){
        same = diff;
        diff = total * (k-1);
        total = same + diff;
    }

    return total;
}

int main(void){
    int n, k;

    printf("Enter the number of posts: ");
    scanf("%d", &n);

    printf("Enter the number of colors: ");
    scanf("%d", &k);

    printf("Number of ways to paint the fence: %lld", computeWaystoPaintFence(n, k));

    return 0;
}