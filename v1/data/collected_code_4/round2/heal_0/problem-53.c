#include <stdio.h>
#include <string.h>

int are_first_and_last_char_equal(char* str) {
    int len = strlen(str);
    return (len > 0 && str[0] == str[len-1]);
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof str, stdin); // Getting the string from the user

    // Removing the newline character from the string if exists
    str[strcspn(str, "\n")] = 0;

    if (are_first_and_last_char_equal(str))
        printf("First and last characters are equal\n");
    else
        printf("First and last characters are not equal\n");

    return 0;
}