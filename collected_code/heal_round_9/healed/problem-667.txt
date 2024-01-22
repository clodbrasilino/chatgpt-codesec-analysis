#include<stdio.h>
#include<string.h>

#define MAX_SIZE 101

int countVowels(const char *str) {
    int i = 0, count = 0;
    int str_length = strnlen(str, MAX_SIZE);

    if(str == NULL)
        return 0;

    for(i = 0; i < str_length && str[i]; i++) {
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
           str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            count++;
        }
    }

    return count;
}

int main() {
    char str[MAX_SIZE];
    printf("Enter a string: ");
    int fgets_status = fgets(str, MAX_SIZE, stdin);

    if(fgets_status != NULL) {
        str[strcspn(str, "\n")] = 0;

        int vowels = countVowels(str);
        printf("Number of vowels: %d\n", vowels);
    } 

    return 0;
}