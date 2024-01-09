#include<iostream>
#include<array>
#include<vector>

using namespace std;

void print(int a[])
{
	for (int i = 0; i < 6; i++)
		cout << a[i] << "\t";
	cout << endl;
}

void printall(vector<int> v)
{
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << "\t";
	cout << endl;
}

void swap(int &x1, int &x2)
{
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
}

void insertionSort(int a[])
{
	int i, j, key;

	for (i = 1; i < 6; i++)
	{
		j = i - 1;
		key = a[i];
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
	print(a);
}

void selectionSort(int a[])
{
	int i, j, min;
	for (i = 0; i < 6; i++)
	{
		min = i;
		for (j = i; j < 6; j++)
		{
			if (a[j] < a[min])
				min = j;
		}
		swap(a[i], a[min]);
	}
	print(a);
}

void bubbleSort(int a[])
{
	int i, j, n = 6;
	for (i = 0; i < n - 2; i++)
	{
		j = n - 1;
		while (j > i)
		{
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
			j--;
		}
	}
	print(a);
}

void shellSort(int a[])
{
	int N = 6;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < N; i++)
		{
			int tmp = a[i];
			int j = i;
			for (; j >= gap && tmp < a[j - gap]; j -= gap)
			{
				a[j] = a[j - gap];
			}
			a[j] = tmp;
		}
	}
	print(a);
}

//Merge Sort
void merge(vector<int> &v, int l, int m, int r)
{
	int i = 0, j = 0, k = 0;
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<int> L(n1 + 1), R(n2 + 1);

	for (; i < n1; i++)
		L[i] = v[l + i];
	for (; j < n2; j++)
		R[j] = v[m + 1 + j];

	i = 0, j = 0, k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] < R[j])
			v[k++] = L[i++];
		else
			v[k++] = R[j++];
	}
	for (; i < n1; i++)
		v[k++] = L[i];
	for (; j < n2; j++)
		v[k++] = R[j];
}
void mergeSort(vector<int> &v, int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		mergeSort(v, l, m);
		mergeSort(v, m + 1, r);
		merge(v, l, m, r);
	}
}

//Quick Sort
int partition(vector<int>& v, int l, int r)
{
	int pivot = v[r];
	int i = l - 1;
	for (int j = l; j < r; j++)
		if (v[j] <= pivot)
			swap(v[++i], v[j]);
	swap(v[i + 1], v[r]);
	return i + 1;
}
void quickSort(vector<int>& v, int l, int r)
{
	if (l < r)
	{
		int q = partition(v, l, r);
		quickSort(v, l, q - 1);
		quickSort(v, q + 1, r);
	}
}

//Heap Sort
//void heapify(int arr[], int n, int i)
//{
//	int largest = i;
//	int l = 2 * i + 1;
//	int r = 2 * i + 2;
//
//	if (l < n && arr[l] > arr[largest])
//		largest = l;
//	if (r < n && arr[r] > arr[largest])
//		largest = r;
//	if (largest != i)
//	{
//		swap(arr[i], arr[largest]);
//		heapify(arr, n, largest);
//	}

	void heapify(int arr[], int n, int i)
	{
		int largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < n && arr[l] < arr[largest])
			largest = l;
		if (r < n && arr[r] < arr[largest])
			largest = r;
		if (largest != i)
		{
			swap(arr[i], arr[largest]);
			heapify(arr, n, largest);
		}
}
void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int main()
{
	int a[6] = { 2,7,1,3,4,5 };
	int b[6] = { 12,17,8,3,5,15 };
	int c[6] = { 41,23,55,47,32,12 };
	int d[6] = { 39,47,15,35,83,78 };
	vector<int> v1 = { 39,47,15,35,83,17,12,78 };
	vector<int> v2 = { 2,8,7,1,3,5,6,4 };
	int e[6] = { 7,4,5,13,22,107 };
	insertionSort(a);
	selectionSort(b);
	bubbleSort(c);
	shellSort(d);
	mergeSort(v1, 0, 7); printall(v1);
	quickSort(v2, 0, 7); printall(v2);
	heapSort(e, 6); print(e);
	system("pause");
	return 0;
}