#include <iostream>
#include <ctime>
using namespace std;

// Arrays
int arr1[] = {1, 2, 3, 4, 5};
int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
              21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
              41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
int arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
              21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
              41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
              61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
              81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

// Utility function to copy arrays
void copyArray(int source[], int destination[], int size)
{
    for (int i = 0; i < size; ++i)
        destination[i] = source[i];
}

// Bubble Sort
void BubbleSort()
{
    cout << "--- Bubble Sort ---" << endl;
    int sizes[] = {5, 10, 50, 100};
    int *arrays[] = {arr1, arr2, arr3, arr4};

    for (int i = 0; i < 4; ++i)
    {
        int temp[100];
        copyArray(arrays[i], temp, sizes[i]);

        clock_t start = clock();
        for (int j = 0; j < sizes[i] - 1; ++j)
            for (int k = 0; k < sizes[i] - j - 1; ++k)
                if (temp[k] > temp[k + 1])
                    swap(temp[k], temp[k + 1]);
        clock_t end = clock();

        double time_taken = double(end - start) * 1000.0 / CLOCKS_PER_SEC;
        cout << "Array of size " << sizes[i] << " sorted in " << time_taken << " ms" << endl;
    }
    cout << endl;
}

// Selection Sort
void SelectionSort()
{
    cout << "--- Selection Sort ---" << endl;
    int sizes[] = {5, 10, 50, 100};
    int *arrays[] = {arr1, arr2, arr3, arr4};

    for (int i = 0; i < 4; ++i)
    {
        int temp[100];
        copyArray(arrays[i], temp, sizes[i]);

        clock_t start = clock();
        for (int j = 0; j < sizes[i] - 1; ++j)
        {
            int min_idx = j;
            for (int k = j + 1; k < sizes[i]; ++k)
                if (temp[k] < temp[min_idx])
                    min_idx = k;
            swap(temp[j], temp[min_idx]);
        }
        clock_t end = clock();

        double time_taken = double(end - start) * 1000.0 / CLOCKS_PER_SEC;
        cout << "Array of size " << sizes[i] << " sorted in " << time_taken << " ms" << endl;
    }
    cout << endl;
}

// Insertion Sort
void InsertionSort()
{
    cout << "--- Insertion Sort ---" << endl;
    int sizes[] = {5, 10, 50, 100};
    int *arrays[] = {arr1, arr2, arr3, arr4};

    for (int i = 0; i < 4; ++i)
    {
        int temp[100];
        copyArray(arrays[i], temp, sizes[i]);

        clock_t start = clock();
        for (int j = 1; j < sizes[i]; ++j)
        {
            int key = temp[j];
            int k = j - 1;
            while (k >= 0 && temp[k] > key)
            {
                temp[k + 1] = temp[k];
                k--;
            }
            temp[k + 1] = key;
        }
        clock_t end = clock();

        double time_taken = double(end - start) * 1000.0 / CLOCKS_PER_SEC;
        cout << "Array of size " << sizes[i] << " sorted in " << time_taken << " ms" << endl;
    }
    cout << endl;
}

// Merge Sort Helper Functions
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[50], R[50];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Merge Sort
void MergeSort()
{
    cout << "--- Merge Sort ---" << endl;
    int sizes[] = {5, 10, 50, 100};
    int *arrays[] = {arr1, arr2, arr3, arr4};

    for (int i = 0; i < 4; ++i)
    {
        int temp[100];
        copyArray(arrays[i], temp, sizes[i]);

        clock_t start = clock();
        mergeSort(temp, 0, sizes[i] - 1);
        clock_t end = clock();

        double time_taken = double(end - start) * 1000.0 / CLOCKS_PER_SEC;
        cout << "Array of size " << sizes[i] << " sorted in " << time_taken << " ms" << endl;
    }
    cout << endl;
}

int main()
{
    BubbleSort();
    SelectionSort();
    InsertionSort();
    MergeSort();
    return 0;
}