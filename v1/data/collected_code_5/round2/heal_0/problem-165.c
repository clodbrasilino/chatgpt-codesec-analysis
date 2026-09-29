#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_same_position_chars(char *str){
    int upper, lower, count = 0;
    for(int i=0; str[i] != '\0'; i++){
        upper = i + 'A'; 
        lower = i + 'a'; 
        if((int)str[i] == upper || (int)str[i] == lower) 
        count++;
    }
    return count;
}

int main() {
    char str[100];
    printf("Please, enter a string: ");
    fgets(str, 100, stdin); 
    str[strcspn(str, "\n")] = 0; 

    int result = count_same_position_chars(str);
    printf("The count of characters at their corresponding alphabet position is: %d\n", result);

    return 0;
}