#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[100];

    printf("Enter the first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter the second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    remove_chars(str1, str2);

    printf("Result: %s\n", str1);

    return 0;
}