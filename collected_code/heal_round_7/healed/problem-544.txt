#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flattenTuple(int* tuple, int size) {
    int strSize = 20 * size;
    char *str = (char*) calloc(strSize, sizeof(char));

    if (str == NULL)
        return NULL;

    for (int i = 0; i < size; i++) {
        char num[20];
        snprintf(num, sizeof(num), "%d", tuple[i]);

        size_t len = strlen(num);
        size_t remaining = strSize - strlen(str);
        
        if(len < remaining) {
            strncat(str, num, len);
        } else {
            break;
        }

        if (i < size - 1 && remaining > 1) {
            strncat(str, ",", 1);
        }
    }

    return str;
}

int main() {
   int tuple[] = {1, 2, 3, 4, 5};
   int size = sizeof(tuple) / sizeof(tuple[0]);
   char* result = flattenTuple(tuple, size);

   if (result == NULL) {
      printf("Memory allocation failed\n");
      return -1;
   }
   
   printf("%s\n", result);
   free(result);
   return 0;
}