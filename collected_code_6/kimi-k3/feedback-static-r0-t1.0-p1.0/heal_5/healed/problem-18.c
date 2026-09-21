#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void remove_chars(char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) {
        return;
    }

    bool char_table[256] = {false};
    size_t i;
    size_t write_pos = 0;
    size_t read_pos = 0;

    for (i = 0; str2[i] != '\0'; i++) {
        char_table[(unsigned char)str2[i]] = true;
    }

    while (str1[read_pos] != '\0') {
        if (!char_table[(unsigned char)str1[read_pos]]) {
            str1[write_pos] = str1[read_pos];
            write_pos++;
        }
        read_pos++;
    }
    str1[write_pos] = '\0';
}

int main(void)
{
    char *str1 = NULL;
    char *str2 = NULL;
    size_t len1 = 0;
    size_t len2 = 0;
    ssize_t read1;
    ssize_t read2;

    printf("Enter the first string: ");
    read1 = getline(&str1, &len1, stdin);
    if (read1 == -1) {
        free(str1);
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter the second string: ");
    read2 = getline(&str2, &len2, stdin);
    if (read2 == -1) {
        free(str1);
        free(str2);
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    remove_chars(str1, str2);

    printf("Result: %s\n", str1);

    free(str1);
    free(str2);

    return 0;
}