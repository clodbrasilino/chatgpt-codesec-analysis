#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_duplicates(char *str, char c) {
    if (str == NULL) {
        return;
    }

    int i = 0;
    int j = 0;
    int found = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            if (!found) {
                str[j++] = str[i];
                found = 1;
            }
        } else {
            str[j++] = str[i];
            found = 0;
        }
        i++;
    }
    str[j] = '\0';
}

int main(void) {
    char str[] = "Thiis is a teeest sttringg withh multiiiple  spacess.";
    
    printf("%s\n", str);
    
    replace_duplicates(str, 'i');
    replace_duplicates(str, 'e');
    replace_duplicates(str, 't');
    replace_duplicates(str, 'g');
    replace_duplicates(str, 'h');
    replace_duplicates(str, ' ');
    replace_duplicates(str, 's');
    
    printf("%s\n", str);

    return 0;
}