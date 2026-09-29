#include <stdio.h>

void calculateDigitsAndLetters(const char* str, int* numOfDigits, int* numOfLetters){
    *numOfDigits = 0;
    *numOfLetters = 0;

    for(int i = 0; str[i] !='\0'; i++){
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
            (*numOfLetters)++;
        }
        else if(str[i]>='0' && str[i]<='9'){
            (*numOfDigits)++;
        }
    }
}

int main() {
    const char* str = "Hello123World456";

    int numOfDigits = 0;
    int numOfLetters = 0;

    calculateDigitsAndLetters(str, &numOfDigits, &numOfLetters);
  
    printf("Number of digits: %d\n", numOfDigits);
    printf("Number of letters: %d\n", numOfLetters);

    return 0;
}