#include<stdio.h>
#include<string.h>

#define MAX_SIZE 101

int countVowels(const char *str) {
    int i = 0, count = 0;
    int str_length = strlen(str);
    
    while(i < str_length && str[i]) {
        if(str[i] == 'a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u' || 
           str[i]=='A' || str[i]=='E' || str[i]=='I' || str[i]=='O' || str[i]=='U') {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    char str[MAX_SIZE] = {0};

    printf("Enter a string: ");
    
    if(fgets(str, MAX_SIZE, stdin) != NULL) {
        str[strcspn(str, "\n")] = 0;

        int vowels = countVowels(str);

        printf("Number of vowels: %d\n", vowels);
    } 

    return 0;
}