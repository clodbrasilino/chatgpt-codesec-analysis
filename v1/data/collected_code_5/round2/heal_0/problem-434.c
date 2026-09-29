#include <stdio.h>
#include <string.h>

int match_ab(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'a') {
            if (str[i+1] != 'b') {
                return 0;
            }
            do {
                i++;
            } while (str[i] == 'b');
        }
    }
    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin); 
    
    str[strcspn(str, "\n")] = 0;

    if (match_ab(str)) {
        printf("The string contains an a followed by b.. \n");
    } else {
        printf("The string doesn't contain an a followed by b.. \n");
    }

    return 0;
}