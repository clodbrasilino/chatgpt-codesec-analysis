#include <string.h>

void concatenateStrings(char str1[], char str2[], char result[]){
    strcpy(result, str1);
    strcat(result, str2);
}