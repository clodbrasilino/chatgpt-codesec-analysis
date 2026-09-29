#include <stdio.h>
#include <string.h>

void removeWords(char** strings, int size, char* characterOrString) {
   int i, j, k;

   for (i = 0; i < size; i++) {
      for (j = k = 0; strings[i][j] != '\0'; j++) {
         int match = 0;
         int limit = strlen(characterOrString);

         while (strings[i][j] == characterOrString[match] && match < limit && strings[i][j] != '\0') {
            j++;
            match++;
         }

         if (match == limit) {
            while (strings[i][j] != '\0') {
               strings[i][k++] = strings[i][j++];
            }
         }

         strings[i][k] = '\0';
      }
   }
}

int main() {
   char* strings[] = {"hello", "world", "example"};
   int size = sizeof(strings) / sizeof(strings[0]);
   char* characterOrString = "o";

   removeWords(strings, size, characterOrString);

   for (int i = 0; i < size; i++) {
      printf("%s\n", strings[i]);
   }

   return 0;
}