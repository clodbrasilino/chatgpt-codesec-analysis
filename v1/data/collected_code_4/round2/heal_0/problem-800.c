#include <stdio.h>

void remove_spaces(char* str){
    
    int count = 0;
    for (int i = 0; str[i]; i++){
        if (str[i] != ' '){
            str[count++] = str[i]; 
        }
    }
    str[count] = '\0';
}

int main(){
    
    char str[] = "Let's remove all whitespaces!";
    remove_spaces(str);
    printf("String without whitespaces: %s", str);
    return 0;
}