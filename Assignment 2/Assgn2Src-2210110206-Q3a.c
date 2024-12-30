#include <stdio.h>
#include <stdlib.h>
void performBinarySearch(int array[], int size, int key) {
    int left = 0, right = size - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (array[mid] == key) {
            printf("Element %d found at index %d\n", key, mid);
            return;
        } else if (array[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Element %d not found\n", key);
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <array_size> <array_elements...>\n", argv[0]);
        return 1;
    }
    int size = atoi(argv[1]);
    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = atoi(argv[i + 2]);
    }
    int key;
    printf("Enter the element to search: ");
    scanf("%d", &key);
    performBinarySearch(array, size, key);
    return 0;
}
