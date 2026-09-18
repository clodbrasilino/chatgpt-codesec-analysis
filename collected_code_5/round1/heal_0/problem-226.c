#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_odd_characters(char* str){
    int length = strlen(str);
    char* new_str = (char*)malloc(sizeof(char) * (length/2 + 1));
    int j = 0;
    
    if(new_str == NULL){
        printf("Failed to allocate memory\n");
        return NULL;
    }

    for(int i = 0; i < length; i++){
      if(i % 2 == 0){
        new_str[j++] = str[i];
      }
    }

    new_str[j] = '\0';
    return new_str;
}

int main() {
    char str[] = "Hello world!";
    char* new_str = remove_odd_characters(str);
    
    if(new_str != NULL){
        printf("%s\n", new_str);
        free(new_str);
    }

    return 0;
}