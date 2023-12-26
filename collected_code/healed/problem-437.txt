#include<stdio.h>
#include<string.h>

void removeOddCharacters(char *str) {
    int i,j=0;
    int len = strlen(str);
    for (i = 0; i<len; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[101] = {0};
  
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
  
    removeOddCharacters(str);
  
    printf("Modified string: %s\n", str);
  
    return 0;
}