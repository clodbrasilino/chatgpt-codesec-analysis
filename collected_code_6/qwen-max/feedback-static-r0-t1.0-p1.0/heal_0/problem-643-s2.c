#include <stdio.h>
#include <string.h>
#include <ctype.h>

int contains_z_in_middle(const char *word) {
    int len = strlen(word);
    for (int i = 1; i < len - 1; ++i) {
        if (word[i] == 'z' && isalpha(word[i-1]) && isalpha(word[i+1])) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char *test_words[] = {"amazing", "zebra", "lazy", "zipped", "pizzazz", "fizzled"};
    int num_words = sizeof(test_words) / sizeof(test_words[0]);

    for (int i = 0; i < num_words; ++i) {
        if (contains_z_in_middle(test_words[i])) {
            printf("%s: Found 'z' in the middle\n", test_words[i]);
        } else {
            printf("%s: No 'z' found in the middle\n", test_words[i]);
        }
    }

    return 0;
}