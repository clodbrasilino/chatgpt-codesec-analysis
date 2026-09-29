#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **convert(char **input, const char *delim, int size) {
    if(input == NULL || delim == NULL || size <= 0) return NULL;
    
    char **output = (char **)calloc(2*size + 1 , sizeof(char *));
    if(output == NULL) return NULL;
    
    for(int i = 0; i < size; i++){
        output[2 * i] = strdup(input[i]);
        if (output[2 * i] == NULL) {
            for(int j = 0; j < i; j++){
                free(output[2 * j]);
            }
            free(output);
            return NULL;  
        }
        output[2 * i + 1] = strdup(delim);
        if (output[2 * i + 1] == NULL) {
            for(int j = 0; j <= i; j++){
                free(output[2 * j]);
                if(j!=i) free(output[2 * j + 1]);
            }
            free(output);
            return NULL;
        }
    }
    return output;
}

void freeList(char **list, int size) {
    if(list != NULL) {
        for(int i = 0; i < size; i++) {
            free(list[i]);
        }
        free(list);
    }
}

int main(){
    int size = 3;
    char delim[] = "string";
    char **input = (char **)malloc(size * sizeof(char *));
    
    if(input == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;  
    }
    for(int i = 0; i < size; i++) {
        input[i] = (char *)malloc(10*sizeof(char));
        if(input[i] == NULL) {
            for(int j = 0; j < i; j++){
                free(input[j]);
            }
            free(input);
            fprintf(stderr, "Failed to allocate memory\n");
            return 1;  
        }
        sprintf(input[i],"ele%d",i+1);
    }

    char **output = convert(input, delim, size);
    
    if(output == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        freeList(input, size);
        return 1;
    }
    
    for(int i = 0; i < 2*size; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");

    freeList(input, size);
    freeList(output, 2*size + 1);
    return 0;
}