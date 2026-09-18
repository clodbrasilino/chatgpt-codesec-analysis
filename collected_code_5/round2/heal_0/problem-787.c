#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(char* str){
    int len = strlen(str);
    for(int i = 0; i < len-3; i++){
        if(str[i]=='a' && str[i+1]=='b' && str[i+2]=='b' && str[i+3]=='b')
            return true;
    }
    return false;
}

int main(){
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    
    if(match_pattern(str)){
        printf("Match Found\n");
    }else{
        printf("Match Not Found\n");
    }
    
    return 0;
}