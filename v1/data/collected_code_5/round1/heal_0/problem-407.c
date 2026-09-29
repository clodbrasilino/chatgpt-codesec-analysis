#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (const void * a, const void * b) {
   return ( *(char*)a - *(char*)b );
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

long long nextBiggerNumber(long long n) {
    char str[20];
    sprintf(str, "%lld", n);

    int len = strlen(str);
    int i;
    for (i = len - 1; i > 0; i--){
        if (str[i] > str[i-1]){
            break;
        }
    }
    if (i == 0) {
        return -1;
    } else {
        char x = str[i-1];
        int smallest = i;
        for (int j = i+1; j < len; j++){
            if (str[j] > x && str[j] < str[smallest]){
                smallest = j;
            }
        }
        swap(&str[smallest], &str[i-1]);
        qsort(&str[i], len - i, sizeof(0), compare);
    }
    return atoll(str);
}

int main() {
    long long n;
    printf("Enter the number: ");
    scanf("%lld", &n);

    long long next = nextBiggerNumber(n);

    if (next == -1) {
        printf("No Number Greater Than The Current Number Can Be Formed.\n");
    } else {
        printf("The Next Greater Number: %lld\n", next);
    }

    return 0;
}