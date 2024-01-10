#include <stdio.h>

void calculateDigitsAndLetters(const char* str, int* numOfDigits, int* numOfLetters){
    *numOfDigits = 0;
    *numOfLetters = 0;

    for(int i=0; str[i]!='\0'; i++){
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
            (*numOfLetters)++;
        }
        else if(str[i]>='0' && str[i]<='9'){
            (*numOfDigits)++;
        }
    }
}

int main(){
    const char* str = "Hello123World456";

    int numOfDigits, numOfLetters;
    /* Possible weaknesses found:
     *  Cannot determine that 'numOfDigits' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'numOfLetters' is initialized [premium-bughuntingUninit]
     */
    calculateDigitsAndLetters(str, &numOfDigits, &numOfLetters);

    /* Possible weaknesses found:
     *  Cannot determine that 'numOfDigits' is initialized [premium-bughuntingUninit]
     */
    printf("Number of digits: %d\n", numOfDigits);
    /* Possible weaknesses found:
     *  Cannot determine that 'numOfLetters' is initialized [premium-bughuntingUninit]
     */
    printf("Number of letters: %d\n", numOfLetters);

    return 0;
}