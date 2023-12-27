#include <stdio.h>
#include <string.h>

void concatenateStrings(const char *str1, const char *str2, char *result, size_t resultSize){
    strncpy(result, str1, resultSize);
    result[resultSize - 1] = '\0';
    size_t len = strlen(result);
    if(len < resultSize - 1){
        strncat(result, str2, resultSize - len - 1);
    }
}

int main(){
    char str1[50] = "Hello, ";
    char str2[50] = "world!";
    char result[100] = "";

    concatenateStrings(str1, str2, result, sizeof(result));

    printf("%s\n", result);
    return 0;
}