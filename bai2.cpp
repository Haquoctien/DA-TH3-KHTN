#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstring>
using namespace std;
void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void bubbleSort(int a[], int n);
void interchangeSort(int a[], int n);
void heapify(int a[], int head, int n);
void buildHeap(int a[], int n);
void heapSort(int a[], int n);
void merge(int a[], int l, int r);
void mergeSort(int a[], int l, int r);
void mergeSort(int a[], int n)
{
    mergeSort(a, 0, n - 1);
}
void quickSort(int a[], int l, int r);
void quickSort(int a[], int n)
{
    quickSort(a, 0, n - 1);
}
void radixSort(int a[], int n);
bool isSorted(int array[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i] > array[i + 1])
            return false;
    }
    return true;
}

typedef void (*sortAlgFuncPtr)(int[], int);
struct sortAlg
{
    sortAlgFuncPtr funcPtr;
    time_t time;
    string name;
};
int main(int argc, char const *argv[])
{
    sortAlg myAlgs[8] = {
        {&selectionSort, 0, "selection"},
        {&insertionSort, 0, "insertion"},
        {&bubbleSort, 0, "bubble"},
        {&interchangeSort, 0, "interchange"},
        {&heapSort, 0, "heap"},
        {&mergeSort, 0, "merge"},
        {&quickSort, 0, "quick"},
        {&radixSort, 0, "radix"}};
    cout << "Nhap n de tao mang co n phan tu ngau nhien "
         << "\n(nhap n > 10000 de thay ro khac biet trong thoi gian):";
    int n;
    cin >> n;
    int *array = new int[n];
    srand(time(NULL));
    for (int j = 0; j < n; array[j] = rand() % (n + 1), j++)
        ;
    time_t t;
    int *arrayToSort = new int[n];
    for (int i = 0; i < 8; i++)
    {
        memcpy(arrayToSort, array, sizeof(int) * n);
        t = clock();
        myAlgs[i].funcPtr(arrayToSort, n);
        myAlgs[i].time = clock() - t;
        if (isSorted(arrayToSort, n))
            cout << "Sorted in " << double(myAlgs[i].time) / CLOCKS_PER_SEC
                 << "s by " << myAlgs[i].name << " sort" << endl;
    }
    delete[] arrayToSort;
    delete[] array;
	system("pause");
    return 0;
}

void selectionSort(int a[], int n)
{
    int minI;
    for (int i = 0; i < n - 1; i++)
    {
        minI = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[minI] > a[j])
                minI = j;
        }
        swap(a[i], a[minI]);
    }
}

void insertionSort(int a[], int n)
{
    for (int key = 1, holder, insert; key < n; key++)
    {
        holder = a[key];
        insert = key;
        while (insert >= 1 && holder < a[insert - 1])
        {
            a[insert] = a[insert - 1];
            insert--;
        }
        a[insert] = holder;
    }
}

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[j] < a[j - 1])
                swap(a[j], a[j - 1]);
        }
    }
}

void interchangeSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
                swap(a[i], a[j]);
    }
}

void heapify(int a[], int head, int n)
{
    int largerChild;
    while (head * 2 + 1 < n)
    {
        largerChild = head * 2 + 1;
        if (largerChild + 1 < n && a[largerChild] < a[largerChild + 1])
            largerChild += 1;
        if (a[largerChild] > a[head])
            swap(a[largerChild], a[head]);
        head = largerChild;
    }
}

void buildHeap(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, i, n);
}

void heapSort(int a[], int n)
{
    buildHeap(a, n);
    while (n > 0)
    {
        swap(a[0], a[n - 1]);
        n--;
        heapify(a, 0, n);
    }
}
void merge(int a[], int l, int r)
{
    int mid = (l + r) / 2;
    int i = l, j = mid + 1;
    int *temp = new int[r - l + 1], n = 0;
    while (i <= mid || j <= r)
    {
        if ((i <= mid && j <= r) && a[i] < a[j] || j > r)
            temp[n++] = a[i++];
        else
            temp[n++] = a[j++];
    }
    for (int i = 0; i < n; i++)
        a[l + i] = temp[i];
    delete[] temp;
}
void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid + 1, r);
        merge(a, l, r);
    }
}

void quickSort(int a[], int l, int r)
{
    if (l >= r)
        return;
    int i = l, j = r;
    int pivot = a[(l + r) / 2];
    while (i < j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(a[j], a[i]);
            i++;
            j--;
        }
    }
    quickSort(a, l, j);
    quickSort(a, i, r);
}
void radixSort(int *a, int n)
{
    // look for max in a
    int max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    // create temp array to contain sorted elements before transfer to a
    // int temp[100];
    int *temp = new int[n];
    for (int i = 0; i < n; temp[i++] = 0)
        ;
    // start with lowest digit
    int exp = 1;
    // repeat until no digit left
    while (max / exp > 0)
    {
        int bucket[10] = {0};
        for (int i = 0; i < n; i++)
            // bucket[i] has count of numbers with i at log(exp) + 1 -th digit
            bucket[a[i] / exp % 10]++;
        for (int i = 1; i < 10; i++)
            // now bucket[i] has last pos of number(s) with i at log(exp) + 1 -th digit
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            // going backward, assign a[i] to last pos of a[i] according to bucket, decrement last pos BEFORE assign
            // cause pos start from 0 not 1 and have to decrement to assign more anyway
            temp[--bucket[a[i] / exp % 10]] = a[i];
        }
        for (int i = 0; i < n; i++)
            a[i] = temp[i];
        exp *= 10;
    }
    delete[] temp;
}