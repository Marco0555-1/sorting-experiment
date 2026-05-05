#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

// --- 1. Bubble Sort ---
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// --- 2. Selection Sort ---
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// --- 3. Insertion Sort ---
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// --- 4. Merge Sort ---
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// --- 5. Quick Sort ---
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// --- 6. Shell Sort ---
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// --- 7. Heap Sort ---
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// --- 8. Counting Sort ---
// Works for non-negative integers (values 0..MAX_VAL)
void countingSort(int arr[], int n) {
    if (n <= 0) return;

    int max_val = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max_val) max_val = arr[i];

    int *count = (int *)calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < n; i++) count[arr[i]]++;
    int idx = 0;
    for (int v = 0; v <= max_val; v++)
        while (count[v]-- > 0) arr[idx++] = v;
    free(count);
}

// --- 9. Radix Sort ---
void countingSortByDigit(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void radixSort(int arr[], int n) {
    if (n <= 0) return;
    int max_val = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max_val) max_val = arr[i];
    for (int exp = 1; max_val / exp > 0; exp *= 10)
        countingSortByDigit(arr, n, exp);
}

void runExperiment(int size, int iterations) {
    int *original = (int *)malloc(size * sizeof(int));
    int *testArr  = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) original[i] = rand() % 10000;

    printf("\n--- Testing Size: %d (Iterations: %d) ---\n", size, iterations);

    const char *names[] = {
        "Bubble", "Selection", "Insertion", "Merge", "Quick",
        "Shell", "Heap", "Counting", "Radix"
    };

    for (int type = 0; type < 9; type++) {
        clock_t start = clock();
        for (int it = 0; it < iterations; it++) {
            copyArray(original, testArr, size);
            if      (type == 0) bubbleSort(testArr, size);
            else if (type == 1) selectionSort(testArr, size);
            else if (type == 2) insertionSort(testArr, size);
            else if (type == 3) mergeSort(testArr, 0, size - 1);
            else if (type == 4) quickSort(testArr, 0, size - 1);
            else if (type == 5) shellSort(testArr, size);
            else if (type == 6) heapSort(testArr, size);
            else if (type == 7) countingSort(testArr, size);
            else if (type == 8) radixSort(testArr, size);
        }
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-10s: %f seconds\n", names[type], time_taken);
    }

    free(original);
    free(testArr);
}

int main() {
    srand(time(NULL));

    runExperiment(50, 10000);
    runExperiment(1000, 100);

    printf("\n* Note: Starting Large Scale Test (N=20,000) *\n");
    runExperiment(20000, 1);

    printf("\nDone! Press any key to exit.\n");
    getchar();
    return 0;
}

