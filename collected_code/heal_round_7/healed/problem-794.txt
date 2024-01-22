#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 102

int matchString(const char* str, size_t len) {
    int i;
    for(i = 0; i < len - 2; i++){
        if(str[i] == 'a' && str[i + 2] == 'b'){
            return 1;
        }
    } 
    return 0;
}

int main() {
    char *str = malloc(sizeof(char) * MAX_LEN);
    if(str == NULL){
        perror("Unable to allocate memory for the string.");
        return 1;
    }
    printf("Enter a string: ");
    if(fgets(str, MAX_LEN, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        size_t len = strnlen(str, MAX_LEN - 1);
        int result = matchString(str, len);
        if(result){
            printf("String matches the pattern.\n");
        }else{
            printf("String does not match the pattern.\n");
        }
    }
    free(str);
    return 0;
}