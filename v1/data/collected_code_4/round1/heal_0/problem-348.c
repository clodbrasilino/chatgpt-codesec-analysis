#include <stdio.h>
#include <stdlib.h>

int countSequences(int values[], int n, int len, int sum) {
    if (len == 0) 
        return sum >= 0;
   
    int result = 0;
    for (int i = 0; i < n; i++) 
        if (sum - values[i] >= 0)
            result += countSequences(values, n, len - 1, sum - values[i]);

    return result;
}

int countAllValidSequences(int values[], int n, int len) {
    int result = 0;
    for (int sum = 0; sum <= len; sum++) 
        result += countSequences(values, n, len, sum);
    return result;
}

int main() {
    int values[] = {1, 2, 3};
    int n = sizeof(values)/sizeof(values[0]);
    int len = 3;
    printf("%d\n", countAllValidSequences(values, n, len));
    return 0;
}