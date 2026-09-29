#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* concatenate(char **tuple, char *delimiter, int tuple_size) {
    int i;
    int total_length = 0;

    for(i = 0; i < tuple_size; ++i) {
        total_length += strlen(tuple[i]);
    }

    total_length += strlen(delimiter)*(tuple_size - 1);

    char *concatenated = (char *) malloc(sizeof(char)*(total_length + 1));
    if(concatenated == NULL) {
        printf("Memory allocation failure\n");
        return NULL;
    }

    concatenated[0] = '\0';

    for(i = 0; i < tuple_size; ++i) {
        strcat(concatenated, tuple[i]);
        if(i < tuple_size - 1) {
            strcat(concatenated, delimiter);
        }
    }

    return concatenated;
}

int main() {
    int tuple_size = 3;
    char *delimiter = ",";
    char *tuple[] = {"Hello", "World", "C_Language"};

    char *result = concatenate(tuple, delimiter, tuple_size);
    if (result == NULL) {
        return 1;
    }

    printf("%s\n", result);
    
    free(result);

    return 0;
}