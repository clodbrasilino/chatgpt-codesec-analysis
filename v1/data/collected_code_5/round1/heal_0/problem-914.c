#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool hasAlternatingChars(const char *s) {
    char first = '\0', second = '\0';
    int i = 0;
    while(s[i] != '\0'){
        if(i==0){
            first = s[i];
        } else if(s[i]!=first) {
            if(second == '\0'){
                second = s[i];
            } else if(s[i]!=second){
                return false;
            }
        } else if(i>0 && s[i]==s[i-1]){
            return false;
        }
        i++;
    }
    return true;
}

int main() {
    char *s1 = "ABABABAB";
    char *s2 = "AAABBB";
    char *s3 = "ABCABCABC";

    printf("Test 1: %s\n", hasAlternatingChars(s1)? "True":"False");
    printf("Test 2: %s\n", hasAlternatingChars(s2)? "True":"False");
    printf("Test 3: %s\n", hasAlternatingChars(s3)? "True":"False");

    return 0;
}