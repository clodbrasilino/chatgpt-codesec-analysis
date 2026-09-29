#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str){
    if(str == NULL) return NULL;
    
    char* result = (char*) malloc(strlen(str) + 1);
    if(result == NULL) return NULL;
    
    result[0] = '\0';
    char* word = strtok(str, " ");
    
    if(word != NULL){
        strcat(result, word);
        strcat(result, " ");
        
        while(word != NULL){
            word = strtok(NULL, " ");
            if(word != NULL && !strstr(result, word)){
                strcat(result, word);
                strcat(result, " ");
            }
        }
    }
    return result;
}

int main(){
    char str[] = "This is a test. This is only a test.";
    char* result = removeDuplicates(str);

    if(result != NULL){
        printf("%s\n", result);
        free(result);
    }
    return 0;
}