#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int find_most_common_character(const char *str, char *most_common);

int find_most_common_character(const char *str, char *most_common) {
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;
    size_t i;
    char best_char = '\0';

    if (str == NULL || most_common == NULL || str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        frequencies[current_char]++;
        
        if (frequencies[current_char] > max_frequency) {
            max_frequency = frequencies[current_char];
            best_char = (char)current_char;
        }
    }

    *most_common = best_char;
    return 0;
}

int main(void) {
    const char *test_string = "experienced c developer";
    char result = '\0';

    if (find_most_common_character(test_string, &result) == 0) {
        printf("%c\n", result);
    }

    if (find_most_common_character(NULL, &result) != 0) {
        printf("NULL pointer handled gracefully\n");
    }

    if (find_most_common_character("", &result) != 0) {
        printf("Empty string handled gracefully\n");
    }

    return EXIT_SUCCESS;
}