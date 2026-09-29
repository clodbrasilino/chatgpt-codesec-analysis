#include <stdio.h>
#include <string.h>

void removeWords(char** strings, int size, char* characterOrString) {
   int i, j, k;

   for (i = 0; i < size; i++) {
      /* Possible weaknesses found:
       *  Cannot determine that 'strings[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      for (j = k = 0; strings[i][j] != '\0'; j++) {
         int match = 0;
         /* Possible weaknesses found:
          *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
          *  Cannot determine that 'characterOrString[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
          */
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

         /* Possible weaknesses found:
          *  write to string literal [-Wanalyzer-write-to-string-literal]
          */
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