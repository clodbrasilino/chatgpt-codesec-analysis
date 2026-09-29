#include<stdio.h>

#define MAX_SIZE 100

int countVowels(const char *str) {
    int i = 0, count = 0;

    while(str[i]) {
        if(str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u' || 
           str[i]=='A' || str[i]=='E' || str[i]=='I' || str[i]=='O' || str[i]=='U') {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    char str[MAX_SIZE];

    printf("Enter a string: ");
    fgets(str, MAX_SIZE, stdin);

    int vowels = countVowels(str);

    printf("Number of vowels: %d\n", vowels);

    return 0;
}