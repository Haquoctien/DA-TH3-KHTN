#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstring>
using namespace std;
void selectionSort(int a[], int n, long *);
void insertionSort(int a[], int n, long *);
void bubbleSort(int a[], int n, long *);
void interchangeSort(int a[], int n, long *);
void heapify(int a[], int head, int n, long *);
void buildHeap(int a[], int n, long *);
void heapSort(int a[], int n, long *);
void merge(int a[], int l, int r, long *);
void mergeSort(int a[], int l, int r, long *);
void mergeSort(int a[], int n, long count[])
{
    mergeSort(a, 0, n - 1, count);
}
void quickSort(int a[], int l, int r, long *);
void quickSort(int a[], int n, long count[])
{
    quickSort(a, 0, n - 1, count);
}
void radixSort(int a[], int n, long *);
void shellSort(int a[], int n, long *);
bool isSorted(int array[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i] > array[i + 1])
            return false;
    }
    return true;
}

typedef void (*sortAlgFuncPtr)(int[], int, long *);
struct sortAlg
{
    sortAlgFuncPtr funcPtr;
    time_t t;
    string name;
    long comparisonCount;
    long assignmentCount;
};
int main(int argc, char const *argv[])
{
    sortAlg myAlgs[9] = {
        {&selectionSort, 0, "selection", 0, 0},
        {&insertionSort, 0, "insertion", 0, 0},
        {&bubbleSort, 0, "bubble", 0, 0},
        {&interchangeSort, 0, "interchange", 0, 0},
        {&heapSort, 0, "heap", 0, 0},
        {&mergeSort, 0, "merge", 0, 0},
        {&quickSort, 0, "quick", 0, 0},
        {&radixSort, 0, "radix", 0, 0},
        {&shellSort, 0, "shell", 0, 0}};
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
        long count[2] = {0};
        t = clock();
        myAlgs[i].funcPtr(arrayToSort, n, count);
        myAlgs[i].t = clock() - t;
        myAlgs[i].comparisonCount = count[0];
        myAlgs[i].assignmentCount = count[1];
        if (isSorted(arrayToSort, n))
        {
            cout << "Sorted in " << double(myAlgs[i].t) / CLOCKS_PER_SEC
                 << "s by " << myAlgs[i].name << " sort" << endl
                 << myAlgs[i].comparisonCount << " comparisons and "
                 << myAlgs[i].assignmentCount << " assignments used to sort."
                 << endl
                 << endl;
        }
        else
            cout << "Not sorted by " << myAlgs[i].name << " sort" << endl
                 << endl;
    }
    delete[] array;
    delete[] arrayToSort;
	system("pause");
    return 0;
}

void selectionSort(int a[], int n, long count[])
{
    for (int i = 0, minI; i < n - 1; i++)
    {
        minI = i;
        for (int j = i + 1; j < n; j++)
        {
            count[0]++;
            if (a[minI] > a[j])
            {
                minI = j;
            }
        }
        if (i != minI)
        {
            swap(a[i], a[minI]);
            count[1] += 3;
        }
    }
}

void insertionSort(int a[], int n, long count[])
{
    for (int i = 1, holder, insert; i < n; i++)
    {
        holder = a[i];
        insert = i;
        count[0] += 1;
        while (insert >= 1 && holder < a[insert - 1])
        {
            a[insert] = a[insert - 1];
            insert--;
            count[1]++;
            count[0]++;
        }
        if (insert != i)
        {
            a[insert] = holder;
            count[1]++;
        }
    }
}

void bubbleSort(int a[], int n, long count[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            count[0]++;
            if (a[j] < a[j - 1])
            {
                swap(a[j], a[j - 1]);
                count[1] += 3;
            }
        }
    }
}

void interchangeSort(int a[], int n, long count[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            count[0]++;
            if (a[i] > a[j])
            {
                swap(a[i], a[j]);
                count[1] += 3;
            }
        }
    }
}

void heapify(int a[], int head, int n, long count[])
{
    int largerChild;
    while (head * 2 + 1 < n)
    {
        largerChild = head * 2 + 1;
        count[0] += 2;
        if (largerChild + 1 < n && a[largerChild] < a[largerChild + 1])
        {
            largerChild += 1;
            count[1]++;
        }
        if (a[largerChild] > a[head])
        {
            swap(a[largerChild], a[head]);
            count[1] += 3;
        }
        else
            return;
        head = largerChild;
    }
}

void buildHeap(int a[], int n, long count[])
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, i, n, count);
}

void heapSort(int a[], int n, long count[])
{
    buildHeap(a, n, count);
    while (n > 0)
    {
        swap(a[0], a[n - 1]);
        count[1] += 3;
        n--;
        heapify(a, 0, n, count);
    }
}
void merge(int a[], int l, int r, long count[])
{
    int mid = (l + r) / 2;
    int i = l, j = mid + 1;
    int *temp = new int[r - l + 1], n = 0;
    while (i <= mid || j <= r)
    {
        count[0] += 1;
        if ((i <= mid && j <= r) && a[i] < a[j] || j > r)
            temp[n++] = a[i++];
        else
            temp[n++] = a[j++];
        count[1] += 1;
    }
    for (int i = 0; i < n; i++)
        a[l + i] = temp[i];
    count[1] += n;
    delete[] temp;
}
void mergeSort(int a[], int l, int r, long count[])
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(a, l, mid, count);
        mergeSort(a, mid + 1, r, count);
        merge(a, l, r, count);
    }
}

void quickSort(int a[], int l, int r, long count[])
{
    if (l >= r)
        return;
    int i = l, j = r;
    int pivot = a[(l + r) / 2];
    while (i < j)
    {
        count[0] += 2;
        while (a[i] < pivot)
        {
            i++;
            count[0]++;
        }
        while (a[j] > pivot)
        {
            j--;
            count[0]++;
        }
        if (i <= j)
        {
            swap(a[j], a[i]);
            i++;
            j--;
            count[1] += 3;
        }
    }
    quickSort(a, l, j, count);
    quickSort(a, i, r, count);
}
void radixSort(int a[], int n, long count[])
{
    // look for max in a
    int max = a[0];
    for (int i = 0; i < n; i++)
    {
        count[0]++;
        if (a[i] > max)
            max = a[i];
    }

    // create temp array to contain sorted elements before transfer to a
    int *temp = new int[n];
    for (int i = 0; i < n; temp[i++] = 0)
        ;
    // start with lowest digit
    int exp = 1;
    // repeat until no digit left
    while (max / exp > 0)
    {
        int bucket[10] = {0};
        for (int i = 0; i < n; i++, count[1]++)
            // bucket[i] has count of numbers with i at log(exp) + 1 -th digit
            bucket[a[i] / exp % 10]++;
        for (int i = 1; i < 10; i++, count[1]++)
            // now bucket[i] has last pos of number(s) with i at log(exp) + 1 -th digit
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--, count[1]++)
        {
            // going backward, assign a[i] to last pos of a[i] according to bucket, decrement last pos BEFORE assign
            // cause pos start from 0 not 1 and have to decrement to assign more anyway
            temp[--bucket[a[i] / exp % 10]] = a[i];
        }
        for (int i = 0; i < n; i++, count[1]++)
            a[i] = temp[i];
        exp *= 10;
    }
    delete[] temp;
}

void shellSort(int a[], int n, long count[])
{
    for (int gap = n / 2; gap >= 1; gap /= 2)
    {
        for (int key = gap; key <= n - 1; key += gap)
        {
            int insert = key, keyHolder = a[key];
            count[0]++;
            while (insert >= gap && keyHolder < a[insert - gap])
            {
                a[insert] = a[insert - gap];
                insert -= gap;
                count[0]++;
                count[1]++;
            }
            if (insert != key)
            {
                a[insert] = keyHolder;
                count[1]++;
            }
        }
    }
}