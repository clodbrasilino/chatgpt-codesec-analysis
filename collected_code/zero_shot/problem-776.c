#include<stdio.h>

int count_vowel_neighbors(char str[]) {
    int count = 0;
    int i = 0;
    
    while(str[i] != '\0') {
        char curr_char = str[i];
        
        if ((curr_char == 'a' || curr_char == 'e' || curr_char == 'i' || curr_char == 'o' || curr_char == 'u' || curr_char == 'A' || curr_char == 'E' || curr_char == 'I' || curr_char == 'O' || curr_char == 'U') &&
            (str[i-1] == 'a' || str[i-1] == 'e' || str[i-1] == 'i' || str[i-1] == 'o' || str[i-1] == 'u' || str[i-1] == 'A' || str[i-1] == 'E' || str[i-1] == 'I' || str[i-1] == 'O' || str[i-1] == 'U') &&
            (str[i+1] == 'a' || str[i+1] == 'e' || str[i+1] == 'i' || str[i+1] == 'o' || str[i+1] == 'u' || str[i+1] == 'A' || str[i+1] == 'E' || str[i+1] == 'I' || str[i+1] == 'O' || str[i+1] == 'U'))
        {
            count++;
        }
        
        i++;
    }
    
    return count;
}

int main() {
    char str[] = "Hello World!";
    int result = count_vowel_neighbors(str);
    printf("Number of characters with vowel neighbors: %d\n", result);
    
    return 0;
}