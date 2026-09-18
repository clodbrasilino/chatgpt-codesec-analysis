#include<stdio.h>

#define MAX 105
#define OFFSET 50

long long dp[MAX][MAX*2][2];

long long count_seqs(int n, int diff, int last_bit){
    if(n==0) return diff==0;

    if(dp[n][diff+OFFSET][last_bit] !=-1)
        return dp[n][diff+OFFSET][last_bit];

    long long count = 0;
    for(int bit=0; bit<2; bit++){
        int new_diff = diff + (bit ? 1 : -1) * (last_bit ? -1 : 1);
        count += count_seqs(n-1, new_diff, bit);
    }
    dp[n][diff+OFFSET][last_bit] = count;
    return count;
}

int count_strings(int n){
    for(int i = 0; i <= 2 * n; i++)
        for(int j = 0; j < 2 * n + OFFSET; j++)
            dp[i][j][0] = dp[i][j][1] = -1;

    return count_seqs(2*n, 0, 0) + count_seqs(2*n, 0, 1);
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    printf("Count of sequences: %d\n", count_strings(n));
    
    return 0;
}