#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100 


char* extract_numbers(const char *input) {
    char* result = malloc(MAX_SIZE);
    if(result == NULL){
        printf("Error, unable to allocate memory"); 
        return NULL;
    }
    int j=0;
    for(int i = 0; input[i] != '\0'; i++) {
        if( isdigit(input[i]) ) {
            result[j++] = input[i];
        }
    }
    result[j]='\0';
    return result;
}

int main(void) {
    const char myString[] = "hello123world456";
    char *numstr = extract_numbers(myString);
    if(numstr != NULL){
        printf("%s\n", numstr);
        free(numstr);
    }else{ 
        return EXIT_FAILURE;
    }   
    return EXIT_SUCCESS;
}