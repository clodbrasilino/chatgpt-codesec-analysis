#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* removeOddIndexedCharacters(char* str) {
    size_t str_len = strlen(str);
    char* str_out = calloc(str_len / 2 + 1, sizeof(char));

    if(str_out == NULL) {
       printf("Memory allocation failed\n");
       exit(1);
    }
    
    for(int i = 0; i < str_len; i += 2){
        str_out[i/2] = str[i];
    }
    
   return str_out;
}

int main() {
   char str[] = "abcdefg";
   char* str_out = removeOddIndexedCharacters(str);
   printf("%s\n", str_out);
   free(str_out);

   return 0;
}