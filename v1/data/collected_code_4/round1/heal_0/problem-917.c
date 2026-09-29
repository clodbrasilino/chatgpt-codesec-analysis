#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findLetterSequences(char* str){

    int length = strlen(str);
    int begin = 0;
    int end = 0;
    int inWord = 0;

    for(int i = 0; i < length; i++){
        if(isupper(str[i]) && inWord == 0) {
            begin = i;
            inWord = 1;
        } else if (inWord == 1 && !islower(str[i])) {
            end = i;
            inWord = 0;
            printf("Sequence found from position %d to %d\n", begin, end-1);
        }
    }
    if (inWord == 1) {
        printf("Sequence found from position %d to %d\n", begin, length - 1);
    }
}

int main(){
    char str[] = "Hello there Mr. RobInsoN";
    findLetterSequences(str);
    return 0;
}