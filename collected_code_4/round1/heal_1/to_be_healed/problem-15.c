#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** string_splitter(char* input_string, int* size){
    int i = 0;
    int len = strlen(input_string);
    char** str_array = malloc((len+1)*sizeof(char*));
    char* buffer = malloc((len+1)*sizeof(char));
    int counter = 0;
    int buffer_size = 0;

    while(i <= len){
        if (input_string[i] == '\0' || islower(input_string[i])){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'buffer' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            buffer[buffer_size] = '\0';
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'str_array' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            str_array[counter] = malloc((buffer_size+1)*sizeof(char));
            strcpy(str_array[counter], buffer);
            counter++;
            buffer_size = 0;
            
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'buffer' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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

   for(i=0; i<size; i++){
       printf("%s\n", str_array[i]);
       free(str_array[i]);
   }
   
   free(str_array);
   return 0;
}