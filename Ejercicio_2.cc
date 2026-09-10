#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int> &A, int p, int r)
{
    for (int i = p + 1; i <= r; i++)
    {
        int key = A[i];
        int j = i - 1;
        while (j >= p && A[j] > key)
        {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

void merge(vector<int> &A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }
}

void hybridMergeSort(vector<int> &A, int p, int r, int k)
{
    if (r - p + 1 <= k)
    {
        insertionSort(A, p, r);
    }
    else if (p < r)
    {
        int q = p + (r - p) / 2;
        hybridMergeSort(A, p, q, k);
        hybridMergeSort(A, q + 1, r, k);
        merge(A, p, q, r);
    }
}

int main()
{
    const int N = 1000000;
    vector<int> ks = {1, 2, 4, 8, 16, 32, 64, 128};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, N);

    vector<int> original_array(N);
    for (int i = 0; i < N; ++i)
    {
        original_array[i] = dis(gen);
    }

    cout << "Tiempos de ejecucion para N = " << N << " elementos:\n\n";

    for (int k : ks)
    {
        vector<int> A = original_array;

        auto inicio = high_resolution_clock::now();
        hybridMergeSort(A, 0, N - 1, k);
        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<milliseconds>(fin - inicio);
        cout << "k = " << k << " \t-> Tiempo: " << duracion.count() << " ms\n";
    }

    return 0;
}