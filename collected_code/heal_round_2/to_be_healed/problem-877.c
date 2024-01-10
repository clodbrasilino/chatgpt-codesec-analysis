#include <stdio.h>
#include <string.h>

void sortString(char *str) {
    if(str == NULL)
        return;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    
    if(len <= 1)
      return;
   
    char temp;

    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    char str[] = "example";

    sortString(str);
    printf("Sorted string: %s\n", str);

    return 0;
}