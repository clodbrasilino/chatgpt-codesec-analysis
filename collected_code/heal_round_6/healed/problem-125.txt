#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

int maxDiff(char* binaryString, size_t size) {
    int maxDiff = 0, currentDiff = 0;
    int count0 = 0, count1 = 0;
    size_t i = 0;

    while (i < size) {
        if (binaryString[i] == '0') {
            count0++;
        }
        else if (binaryString[i] == '1') {
            count1++;
        }
        else {
            return -1;
        }
        currentDiff = count0 - count1;
        if (currentDiff > maxDiff) {
            maxDiff = currentDiff;
        }
        if (currentDiff < 0) {
            count0 = 0;
            count1 = 0;
        }
        i++;
    }
 
    return maxDiff;
}

int main()
{
    char binaryString[MAX_SIZE+1];

    printf("Enter a binary string: \n");
    if(fgets(binaryString, sizeof(binaryString), stdin) != NULL)
    {
        binaryString[strcspn(binaryString, "\n")] = 0;
        if(strlen(binaryString) < MAX_SIZE){
            int result = maxDiff(binaryString, strlen(binaryString) + 1);
            if (result != -1) {
                printf("Maximum difference between 0s and 1s: %d\n", result);
            }
            else {
                printf("Entered string is not a valid binary string\n");
            }
        }
        else{
            printf("Entered string is too long. It should be less than %d characters\n", MAX_SIZE);
        }
    }
    return 0;
}