#include <stdio.h>
#include <stdlib.h>

#define N 1000001

int freq[N] = {0};
  
int maxOccuringDivisor(int left, int right) {
  
    for (int i=1; i<=right; i++)
        for (int j=i; j<=right; j+=i)
            if (j >= left)
                freq[i]++;
  
    int max_divisor = -1;
    int max_freq = -1;
  
    for (int i=1; i<=right; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_divisor = i;
        }
    }
    return max_divisor;
}
  
int main() {
  
    int left = 1, right = 10;
  
    printf("%d", maxOccuringDivisor(left, right));
    return 0;
}