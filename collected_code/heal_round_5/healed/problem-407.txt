#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGIT_COUNT 20

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

long long findNextBigger(char digits[], int n){
    int i, j;
    for (i = n-1; i > 0; i--){
        if (digits[i-1] < digits[i]){
            break;
        }
    }
    if (i == 0){
        return -1;
    }

    int smallest_index = i;
    int x = digits[i-1];
    for (j=i+1; j<n; j++){
        if (digits[j] > x && digits[j] < digits[smallest_index]){
            smallest_index = j;
        } 
    }
       
    swap(&(digits[i-1]), &(digits[smallest_index]));
    qsort(&(digits[i]), n-i, sizeof(digits[0]), compare);
    digits[n] = '\0';
    long long next_bigger = strtoll(digits, NULL, 10);
    
    return next_bigger;
}

int main(){
    long long number;
    printf("Enter a number: ");
    scanf("%lld", &number);

    char digits[MAX_DIGIT_COUNT + 1];
    
    if (snprintf(digits, MAX_DIGIT_COUNT + 1, "%lld", number) >= MAX_DIGIT_COUNT + 1){
        printf("Error: number has more digits than MAX_DIGIT_COUNT.\n");
        return -1;
    }

    int n = strnlen(digits, MAX_DIGIT_COUNT + 1);
    long long next_bigger = findNextBigger(digits, n);
    if (next_bigger == -1){
        printf("No next bigger number possible.\n");
    }
    else{
        printf("Next bigger number: %lld\n", next_bigger);
    }

    return 0;
}