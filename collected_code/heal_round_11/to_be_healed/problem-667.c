#include<stdio.h>
#include<string.h>

#define MAX_SIZE 102

int countVowels(const char *str) {
    int i = 0, count = 0;

    if(str == NULL)
        return 0;

    for(i = 0; i < MAX_SIZE && str[i]; i++) {
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
           str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            count++;
        }
    }

    return count;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = {0};
    printf("Enter a string: ");

    char* fgets_status = fgets(str, MAX_SIZE, stdin);

    if(fgets_status != NULL) {
        str[strcspn(str, "\n")] = 0;

        int vowels = countVowels(str);
        printf("Number of vowels: %d\n", vowels);
    } 

    return 0;
}