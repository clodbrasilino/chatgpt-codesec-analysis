#include <stdio.h>
#include <string.h>

void combineDictionaries(int dict1[], int dict2[], int size1, int size2) {
    int dict3[size1 + size2]; // Combined dictionary
    int i, j, k;

    // Copying values from dict1 to dict3
    for (i = 0; i < size1; i++) {
        dict3[i] = dict1[i];
    }

    // Adding values for common keys
    for (i = 0; i < size2; i++) {
        int flag = 0; // Flag to check if key is already present in dict3

        // Checking if key is already present in dict3
        for (j = 0; j < size1; j++) {
            if (dict2[i] == dict3[j]) {
                dict3[j + size1] += dict2[i + 1]; // Adding values for common key
                flag = 1; // Key is already present
            }
        }

        // Adding new key-value pair to dict3
        if (flag == 0) {
            dict3[size1 + k] = dict2[i]; // Adding new key
            dict3[size1 + k + 1] = dict2[i + 1]; // Adding new value
            k += 2; // Updating index for next key-value pair
        }
    }

    // Printing combined dictionary
    for (i = 0; i < size1 + size2; i += 2) {
        printf("%d: %d\n", dict3[i], dict3[i + 1]);
    }
}

int main() {
    // Sample dictionaries
    int dict1[] = {1, 5, 2, 10};
    int dict2[] = {2, 3, 3, 7, 4, 2};

    int size1 = sizeof(dict1) / sizeof(dict1[0]);
    int size2 = sizeof(dict2) / sizeof(dict2[0]);

    // Combining dictionaries and printing result
    combineDictionaries(dict1, dict2, size1, size2);

    return 0;
}