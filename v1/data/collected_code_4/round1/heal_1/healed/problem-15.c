#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** string_splitter(char* input_string, int* size){
    int i = 0;
    int len = strlen(input_string);
    char** str_array = (char**) malloc((len+1)*sizeof(char*));

    if (str_array == NULL) {
        return NULL;
    }

    char* buffer = (char*) malloc((len+1)*sizeof(char));

    if (buffer == NULL) {
        free(str_array);
        return NULL;
    }

    int counter = 0;
    int buffer_size = 0;

    while(i <= len){
        if (input_string[i] == '\0' || islower(input_string[i])){
            buffer[buffer_size] = '\0';
            str_array[counter] = (char*) malloc((buffer_size+1)*sizeof(char));
            
            if (str_array[counter] == NULL) {
                for (int j = 0; j < counter; j++)
                    free(str_array[j]);
                free(str_array);
                free(buffer);
                return NULL;
            }
            
            strcpy(str_array[counter], buffer);
            counter++;
            buffer_size = 0;
            
        } else {
            buffer[buffer_size] = input_string[i];
            buffer_size++;
        }
        i++;
    }

    free(buffer);
    *size = counter;
    return str_array;
}

int main(){
   char input_string[] = "ThisIsATestString";
   int size,i;

   char** str_array = string_splitter(input_string, &size);

   if (str_array == NULL) {
        return -1;
   }

   for(i=0; i<size; i++){
       printf("%s\n", str_array[i]);
       free(str_array[i]);
   }
   
   free(str_array);
   return 0;
}