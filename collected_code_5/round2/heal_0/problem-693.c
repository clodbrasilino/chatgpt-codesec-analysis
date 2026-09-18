#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

char* removeMultipleSpaces(char* str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[ ]{2,}", REG_EXTENDED);
    if(ret) {
        printf("Could not compile regex\n");
        exit(1);
    }

    char* p = (char*)malloc(strlen(str) + 1);
    if(p == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
  
    char *q = p;
  
    for(char *r = str ; *r != '\0' ; *r++) {
        if (!regexec (&regex, r, 0, NULL, 0)){ 
            if(*q != ' ' || (q > p && *(q - 1) != ' ')) 
                *q++ = *r;
        } else {
            *q++ = *r;
        }
    }
   *q = '\0';
   regfree (&regex);
   return p;
}

int main() {
   char str[] = "This is     a string    with  multiple     spaces.";
   
   char* result = removeMultipleSpaces(str);
   
   printf("Result: %s", result);
   free(result);

   return 0;
}