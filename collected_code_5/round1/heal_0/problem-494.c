#include<stdio.h>
#include<math.h>
#include<string.h>

int binaryTupleToInteger(char *binary){
    int length = strlen(binary);
    int result = 0;
    for(int i = 0; i < length; i++){
        if(binary[i] == '1'){
            result += pow(2, length-i-1);
        } else if(binary[i] != '0') {
            return -1;
        }
    }
    return result;
}

int main(){
    char binary[100];
    printf("Enter binary number : ");
    fgets(binary, 100, stdin);
    
    binary[strcspn(binary, "\n")] = '\0';

    int result = binaryTupleToInteger(binary);
    
    if(result != -1){
        printf("The integer equivalent of binary number %s is : %d", binary, result);
    } else {
        printf("Invalid binary number");
    }
    
    return 0;
}