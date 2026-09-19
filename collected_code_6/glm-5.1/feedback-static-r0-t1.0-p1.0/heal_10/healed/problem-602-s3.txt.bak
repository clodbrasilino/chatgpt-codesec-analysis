#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_first_repeated(const char *str, char *result) {
    if (str == NULL || result == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *count = (char *)calloc(256, sizeof(char));
    if (count == NULL) {
        return -2;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            *result = str[i];
            free(count);
            return 1;
        }
        count[c]++;
    }

    free(count);
    return 0;
}

static void print_result(int ret, char res, const char *test_name) {
    switch (ret) {
        case 1:
            printf("%s: %c\n", test_name, res);
            break;
        case 0:
            printf("%s: No repeated character\n", test_name);
            break;
        case -1:
            printf("%s: Invalid input\n", test_name);
            break;
        case -2:
            printf("%s: Memory allocation failed\n", test_name);
            break;
    }
}

int main(void) {
    const char *test1 = "abcdefa";
    const char *test2 = "abcdef";
    const char *test3 = "";
    const char *test4 = NULL;
    const char *test5 = "hello";

    char res;

    print_result(find_first_repeated(test1, &res), res, "Test 1");
    print_result(find_first_repeated(test2, &res), res, "Test 2");
    print_result(find_first_repeated(test3, &res), res, "Test 3");
    print_result(find_first_repeated(test4, &res), res, "Test 4");
    print_result(find_first_repeated(test5, &res), res, "Test 5");

    return 0;
}