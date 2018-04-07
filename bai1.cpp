#include <iostream>
#include <cstring>
#include <string>
using namespace std;

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

typedef void (*sortAlgFuncPtr)(int[], int);

struct sortAlgs
{
    sortAlgFuncPtr ptr;
    string name;
};

int main(int argc, char const *argv[])
{
    cout << "Nhap so phan tu can nhap: ";
    int n;
    cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Nhap phan tu thu " << i + 1 << ": ";
        cin >> array[i];
    }
    sortAlgs list[3] = {{&quickSort, "quick"},
                        {&mergeSort, "merge"},
                        {&radixSort, "radix"}};
    for (int i = 0; i < 3; i++)
    {
        int *arrayToSort = new int[n];
        memcpy(arrayToSort, array, sizeof(int) * n);
        list[i].ptr(arrayToSort, n);
        cout << "Sorted by " << list[i].name << ": ";
        for (int i = 0; i < n; i++)
            cout << arrayToSort[i] << " ";
        cout << endl;
        delete[] arrayToSort;
    }
    delete[] array;
	system("pause");
    return 0;
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