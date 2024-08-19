#include <stdio.h>
#include <cs50.h>

void merge_sort(int array[], int size);

int array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
int array_len = 9;

int main(void){
    merge_sort(array, array_len);
    for (int i = 0; i < array_len; i++) {
        printf("%i\n", array[i]);
    }
    return 0;
}

void merge_sort(int arr[], int size){
    if (size == 1) {
        return;
    }
    int larr[size/2];
    int rarr[size - size/2];

    for (int i = 0; i < size; i++) {
        if (i < size/2) {
            larr[i] = arr[i];
        }
        else {
            rarr[i - size/2] = arr[i];
        }
    }

    merge_sort(larr, size/2);
    merge_sort(rarr, size - size/2);

    for (int i = 0, l = 0, r = 0; i < size; i++) {
        if (l == size/2) {
            arr[i] = rarr[r];
            r++;
        }
        else if (r == size - size/2) {
            arr[i] = larr[l];
            l++;
        }
        else if (larr[l] < rarr[r]) {
            arr[i] = larr[l];
            l++;
        }
        else {
            arr[i] = rarr[r];
            r++;
        }
    }
    return;
}
