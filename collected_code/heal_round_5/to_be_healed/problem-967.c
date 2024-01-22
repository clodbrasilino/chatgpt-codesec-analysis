#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 256

int checkAllVowels(const char *str) {
    int vowelCount = 0;
    int vcount[5] = {0,0,0,0,0};

    if(str == NULL)
        return 0;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        switch(str[i]) {
            case 'a': case 'A': vcount[0] = 1; break;
            case 'e': case 'E': vcount[1] = 1; break;
            case 'i': case 'I': vcount[2] = 1; break;
            case 'o': case 'O': vcount[3] = 1; break;
            case 'u': case 'U': vcount[4] = 1; break;
            default: break;
        }
    }

    for (size_t i = 0; i < 5; i++) {
        if (vcount[i]) {
            vowelCount++;
        }
    }

    return vowelCount == 5;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_LEN] = {'\0'};

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL){

        str[strcspn(str, "\n")] = 0;

        if (checkAllVowels(str)) {
            printf("The string contains all vowels.\n");
        } else {
            printf("The string does not contain all vowels.\n");
        }    
    }
    return 0;
}