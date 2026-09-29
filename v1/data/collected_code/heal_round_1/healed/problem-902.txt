#include <stdio.h>
#include <string.h>

void combineDictionaries(int* dict1, int* dict2, int size1, int size2) {
    int dict3[size1 + size2];
    int i, j, k = 0;

    for (i = 0; i < size1; i++) {
        dict3[i] = dict1[i];
    }

    for (i = 0; i < size2; i += 2) {
        int flag = 0;

        for (j = 0; j < size1; j += 2) {
            if (dict2[i] == dict3[j]) {
                dict3[j + size1] += dict2[i + 1];
                flag = 1;
            }
        }
        if (flag == 0) {
            dict3[size1 + k] = dict2[i];
            dict3[size1 + k + 1] = dict2[i + 1];
            k += 2;
        }
    }
    for (i = 0; i < size1 + size2; i += 2) {
        printf("%d: %d\n", dict3[i], dict3[i + 1]);
    }
}

int main() {
    int dict1[] = {1, 5, 2, 10};
    int dict2[] = {2, 3, 3, 7, 4, 2};

    int size1 = sizeof(dict1) / sizeof(dict1[0]);
    int size2 = sizeof(dict2) / sizeof(dict2[0]);

    combineDictionaries(dict1, dict2, size1, size2);

    return 0;
}