#include<stdio.h>
#include<string.h>

#define MAX_SIZE 101

int countVowels(const char *str) {
    int i = 0, count = 0;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = {0};

    printf("Enter a string: ");
    
    if(fgets(str, MAX_SIZE, stdin) != NULL) {
        str[strcspn(str, "\n")] = 0;

        int vowels = countVowels(str);

        printf("Number of vowels: %d\n", vowels);
    } 

    return 0;
}