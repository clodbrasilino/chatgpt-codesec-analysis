#include<stdio.h>
#include<string.h>

int minimumSwaps(char *binary_A, char *binary_B, int n) {
    int count = 0;
    int i = 0, j = 0;

    while(i < n) {
        while(i < n && binary_A[i] != binary_B[i]) {
            i++;
        }

        if(i < n) {
            j = i+1;
            while(j < n && binary_A[j] == binary_B[j]) {
                j++;
            }

            if(j < n) {
                char temp = binary_A[i];
                binary_A[i] = binary_A[j];
                binary_A[j] = temp;
                count++;
            }
            i = j;
        }    
    }

    return count;
}

int main() {
    char binary_A[] = "11001";
    char binary_B[] = "01110";
    int n = strlen(binary_A);

    printf("Minimum number of swaps needed: %d\n", minimumSwaps(binary_A, binary_B, n));

    return 0;
}