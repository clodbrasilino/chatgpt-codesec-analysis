#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* runLengthEncoding(char* list);

int main() {
    char list[] = "aaaabbccd";
    char* encodedList = runLengthEncoding(list);

    if(encodedList==NULL){
        printf("Memory allocation failed\n");
        return 1;        
    }

    printf("%s\n", encodedList);
    free(encodedList);

    return 0;
} 

char* runLengthEncoding(char* list) {
    if(list == NULL){
        return NULL;
    }

    int len = strlen(list);
    char* result = (char*)malloc(sizeof(char) * len * 2 + 1);

    if(result == NULL) {
        return NULL;
    }

    int count = 1; 
    int j = 0;

    for(int i = 0; i < len; ++i) {
        if(i < len-1 && list[i] == list[i + 1]) {
            ++count;
        } else {
            j += sprintf(&result[j], "%d%c", count, list[i]);
            count = 1;
        }
    }

    result[j] = '\0';
    
    return result;
}