#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_SIZE 100

bool isValidString(const char* str) {
    return str && strnlen(str, MAX_STR_SIZE) < MAX_STR_SIZE;
}

void removeOccurrences(char* str, const char c) {
    if (!isValidString(str)) {
        return;
    }

    int i, j;
    int len = strnlen(str, MAX_STR_SIZE);
    
    for(i = 0, j = 0; i < len; i++){
        if(str[i] != c){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char* str = malloc(MAX_STR_SIZE * sizeof(char));
    if (!str){
        printf("Memory allocation failed\n");
        return 1;
    }

    char c;

    printf("Enter a string: ");
    fgets(str, MAX_STR_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';  

    printf("Enter a character: ");
    scanf(" %c", &c);
    /* Possible weaknesses found:
     *   Check buffer boundaries if used in a loop including recursive loops  (CWE-120, CWE-20).
     */
    getchar(); // To consume the newline character that was left by scanf

    removeOccurrences(str, c);

    printf("Modified string: %s\n", str);

    free(str);
    return 0;
}