#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sum_is_length(char* str, int n) {
    int count = 0;
    for (int len = 1; len <= n; len++) { 
        for (int i = 0; i <= n - len; i++) { 
            int sum = 0;
            for (int j = 0; j < len; j++) 
                sum += (str[i + j] - '0'); 
  
            if (sum == len)
                count++; 
        } 
    } 
    return count; 
} 

int main() {
    char str[100];
    printf("Enter the string\n");
    scanf("%s", str);
    int len = strlen(str); 
    printf("Number of substrings: %d", 
            sum_is_length(str, len));
    return 0;
}