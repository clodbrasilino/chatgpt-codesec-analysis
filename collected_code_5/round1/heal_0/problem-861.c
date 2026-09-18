#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

int compare(const void *a, const void *b) { 
    return (*(char *)a - *(char *)b); 
} 

int areAnagram(char *str1, char *str2) {
    int n1 = strlen(str1); 
    int n2 = strlen(str2); 

    if (n1 != n2) 
      return 0; 

    qsort(str1, n1, sizeof( char ), compare); 
    qsort(str2, n2, sizeof( char ), compare); 

    for (int i = 0; i < n1;  i++) 
       if (str1[i] != str2[i]) 
         return 0; 

    return 1; 
} 

void findAnagrams(char* str, char** list, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (areAnagram(str, list[i]))
            printf("%s ", list[i]);
    }
}
  
int main() {
    int n = 5;
    char str[] = "listen";
    char* list[] = {"enlists", "google", "inlets", "banana", "istlen"};
  
    findAnagrams(str, list, n);
    return 0;
}