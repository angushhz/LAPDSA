
#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>

using namespace std;

#define ARRAY_SIZE 50000

#define INC_SORT 0
#define DEC_SORT 1

#define MAX_HEAP 0
#define MIN_HEAP 1

class Heap
{
public:
	int *arr;
	int count;
	int capacity;
	int heap_type;

public:
	int getCount() { return count; }
	void CopyData(int *data, int size)
	{
		memcpy(this->arr, data, sizeof(int) * size);
		this->count = size;
	}
	void CreateHeap(int capacity, int heap_type)
	{
		this->heap_type = heap_type;
		this->count = 0;
		this->capacity = capacity;
		this->arr = new int[this->capacity];
		if (this->arr == NULL)
		{
			cout << "Not enough memory";
			exit(-1);
		}
	}
	~Heap()
	{
		delete[] this->arr;
	}
	void ReheapUp(long position)
	{
		if (position > 0)
		{
			long parent = (position - 1) / 2;

			// For max-heap
			if (this->heap_type == MAX_HEAP && this->arr[position] > this->arr[parent])
			{
				int temp = this->arr[position];
				this->arr[position] = this->arr[parent];
				this->arr[parent] = temp;
				ReheapUp(parent);
			}
			// For min-heap
			else if (this->heap_type == MIN_HEAP && this->arr[position] < this->arr[parent])
			{
				int temp = this->arr[position];
				this->arr[position] = this->arr[parent];
				this->arr[parent] = temp;
				ReheapUp(parent);
			}
		}
	}
	void ReheapDown(int position, int lastPosition)
	{
		long leftChild = 2 * position + 1;
		long rightChild = 2 * position + 2;
		long child;

		// For max-heap
		if (this->heap_type == MAX_HEAP)
		{
			if (leftChild <= lastPosition)
			{
				if (rightChild <= lastPosition && this->arr[rightChild] > this->arr[leftChild])
					child = rightChild;
				else
					child = leftChild;

				if (this->arr[child] > this->arr[position])
				{
					int temp = this->arr[child];
					this->arr[child] = this->arr[position];
					this->arr[position] = temp;
					ReheapDown(child, lastPosition);
				}
			}
		}
		// For min-heap
		else if (this->heap_type == MIN_HEAP)
		{
			if (leftChild <= lastPosition)
			{
				if (rightChild <= lastPosition && this->arr[rightChild] < this->arr[leftChild])
					child = rightChild;
				else
					child = leftChild;

				if (this->arr[child] < this->arr[position])
				{
					int temp = this->arr[child];
					this->arr[child] = this->arr[position];
					this->arr[position] = temp;
					ReheapDown(child, lastPosition);
				}
			}
		}
	}
	bool InsertHeap(int DataIn)
	{
		if (this->count == this->capacity)
			return false;
		else
		{
			this->arr[this->count] = DataIn;
			ReheapUp(this->count);
			this->count++;
			return true;
		}
	}
	bool DeleteHeap(int &DataOut)
	{
		if (this->count <= 0)
			return false;
		else
		{
			DataOut = this->arr[0];
			this->arr[0] = this->arr[count - 1];
			count = count - 1;
			ReheapDown(0, count - 1);
			return true;
		}
	}
	void BuildHeap()
	{
		long position = this->count / 2 - 1;

		while (position >= 0)
		{
			ReheapDown(position, count - 1);
			position--;
		}
	}
	bool IsHeap()
	{
		long position = this->count / 2 - 1;
		long lastPosition = this->count - 1;

		while (position >= 0)
		{
			long leftChild = 2 * position + 1;
			long rightChild = 2 * position + 2;
			long child;

			// For max-heap
			if (this->heap_type == MAX_HEAP)
			{
				if (leftChild <= lastPosition)
				{
					if (rightChild <= lastPosition && this->arr[rightChild] > this->arr[leftChild])
						child = rightChild;
					else
						child = leftChild;

					if (this->arr[child] > this->arr[position])
						return false;
				}
			}
			// For min-heap
			else if (this->heap_type == MIN_HEAP)
			{
				if (leftChild <= lastPosition)
				{
					if (rightChild <= lastPosition && this->arr[rightChild] < this->arr[leftChild])
						child = rightChild;
					else
						child = leftChild;

					if (this->arr[child] < this->arr[position])
						return false;
				}
			}
			position--;
		}
		return true;
	}
	void PrintHeap()
	{
		for (long i = 0; i < this->count; i++)
			cout << this->arr[i] << " ";
		cout << endl;
	}
};
int *arr1 = NULL;
Heap heap;

long lrand()
{
#define CHAR_BITS 8
	long r = 0;
	for (int i = 0; i < sizeof(long) / sizeof(int); i++)
	{
		r = r << (sizeof(int) * CHAR_BITS);
		r |= rand();
	}
	return r;
}

bool IsSorted(int nType)
{
	if (nType == DEC_SORT)
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
			if (arr1[i] != ARRAY_SIZE - 1 - i)
				return false;
	}
	else if (nType == INC_SORT)
		for (int i = 0; i < ARRAY_SIZE; i++)
			if (arr1[i] != i)
				return false;

	return true;
}

void ShuffleData(int *arr)
{
	// Shuffle data
	long i;
	srand(time(NULL));
	for (i = ARRAY_SIZE - 1; i > 0; i--)
	{
		long j = lrand() % ARRAY_SIZE;

		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

void InsertionSort(int *arr)
{
	long count = ARRAY_SIZE, current;

	current = 1;

	while (current < count)
	{
		long temp = arr[current];
		long walker = current - 1;

		while (walker >= 0 && temp < arr[walker])
		{
			arr[walker + 1] = arr[walker];
			walker--;
		}

		arr[walker + 1] = temp;
		current++;
	}
}
// TODO
// INC_SORT
void ShellSort(int *arr)
{
	// Implementation for ShellSort function
	int h, i, j, temp;

	for (h = ARRAY_SIZE / 2; h > 0; h /= 2)
	{
		for (i = h; i < ARRAY_SIZE; i++)
		{
			temp = arr[i];
			for (j = i; j >= h && temp < arr[j - h]; j -= h)
			{
				arr[j] = arr[j - h];
			}
			arr[j] = temp;
		}
	}
}
// INC_SORT
void SelectionSort(int *arr)
{
	// Implementation for SelectionSort function
	for (int i = 0; i < ARRAY_SIZE - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < ARRAY_SIZE; j++)
		{
			if (arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
	}
}
// DEC_SORT

void Heapify(int *arr, int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] < arr[largest])
	{ // Change comparison to <
		largest = left;
	}

	if (right < n && arr[right] < arr[largest])
	{ // Change comparison to <
		largest = right;
	}

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		Heapify(arr, n, largest);
	}
}

void HeapSort(int *arr)
{
	int n = ARRAY_SIZE;
	// Build a min-heap
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		Heapify(arr, n, i);
	}

	// Extract elements from the heap in ascending order (reverse of descending)
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		Heapify(arr, i, 0);
	}
}

// INC_SORT
void BubbleSort(int *arr)
{
	// Implementation for BubbleSort function
	for (int i = 0; i < ARRAY_SIZE - 1; i++)
	{
		for (int j = 0; j < ARRAY_SIZE - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
// INC_SORT
int partition(int *arr, int low, int high)
{
	int pivot = arr[high];

	// Index of smaller element and indicates
	// the right position of pivot found so far
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{

		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{

			// Increment index of smaller element
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
void QuickSortHelp(int *arr, int low, int high)
{
	if (low < high)
	{

		// pi is partitioning index, arr[p]
		// is now at right place
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		QuickSortHelp(arr, low, pi - 1);
		QuickSortHelp(arr, pi + 1, high);
	}
}
void QuickSort(int *arr)
{
	QuickSortHelp(arr, 0, ARRAY_SIZE - 1);
}
// INC_SORT
void Merge(int *arr, int left, int mid, int right)
{
	// Implementation for Merge function
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int *L = new int[n1];
	int *R = new int[n2];

	for (int i = 0; i < n1; i++)
	{
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = arr[mid + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}
void MergeSortHelp(int *arr, int left = 0, int right = ARRAY_SIZE - 1)
{
	// Implementation for MergeSort function
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		MergeSortHelp(arr, left, mid);
		MergeSortHelp(arr, mid + 1, right);

		Merge(arr, left, mid, right);
	}
}
void MergeSort(int *arr)
{
	MergeSortHelp(arr);
}
void Sorting(void (*SortFunc)(int *), int nSortType = INC_SORT)
{
	DWORD startTime;
	DWORD endTime;
	long i;
	char strMessage[80];

	if (nSortType == INC_SORT)
		strcpy(strMessage, "The array is sorted in increasing order");
	else
		strcpy(strMessage, "The array is sorted in decreasing order");
	// Sorting random array
	cout << "Sorting an random array ... " << endl;

	startTime = GetTickCount();
	(*SortFunc)(arr1);
	endTime = GetTickCount();

	if (IsSorted(nSortType))
		cout << strMessage << endl;
	else
		cout << "The array is unorder" << endl;

	cout << "Time (ms) :  " << (endTime - startTime) / 1000.0 << endl;

	// Sorting increasing array
	for (i = 0; i < ARRAY_SIZE; i++)
		arr1[i] = i;

	cout << "Sorting an increasing array ... " << endl;

	startTime = GetTickCount();
	(*SortFunc)(arr1);
	endTime = GetTickCount();

	if (IsSorted(nSortType))
		cout << strMessage << endl;
	else
		cout << "The array is unorder" << endl;

	cout << "Time (ms) :  " << (endTime - startTime) / 1000.0 << endl;

	// Sorting decreasing array
	for (i = 0; i < ARRAY_SIZE; i++)
		arr1[i] = ARRAY_SIZE - 1 - i;

	cout << "Sorting an decreasing array ... " << endl;

	startTime = GetTickCount();
	(*SortFunc)(arr1);
	endTime = GetTickCount();

	if (IsSorted(nSortType))
		cout << strMessage << endl;
	else
		cout << "The array is unorder" << endl;

	cout << "Time (ms) :  " << (endTime - startTime) / 1000.0 << endl;
}

int main()
{
	// Create array;
	arr1 = new int[ARRAY_SIZE];

	if (arr1 == NULL)
	{
		cout << "Not enough memory";
		return 0;
	}
	for (long i = 0; i < ARRAY_SIZE; i++)
		arr1[i] = i;
	cout << "ARRAY SIZE: " << ARRAY_SIZE << endl
		 << endl;
	heap.CreateHeap(ARRAY_SIZE, MIN_HEAP);
	heap.CopyData(arr1, ARRAY_SIZE);
	heap.BuildHeap();
	heap.PrintHeap();
	cout << "ARRAY SIZE: " << ARRAY_SIZE << endl
		 << endl;
	cout << "================================================" << endl;
	cout << "			INSERTION SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);
	Sorting(InsertionSort);
	cout << "================================================" << endl;
	cout << "			ShellSort SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);
	Sorting(ShellSort);
	cout << "================================================" << endl;
	cout << "			Selection SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);
	Sorting(SelectionSort);
	cout << "================================================" << endl;
	cout << "			HeapSort SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);
	Sorting(HeapSort, DEC_SORT);
	cout << "================================================" << endl;
	cout << "			BUBBLE SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);

	Sorting(BubbleSort);
	cout << "			Merge SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);
	Sorting(MergeSort);

	cout << "================================================" << endl;
	cout << "			Quick SORT" << endl;
	cout << "================================================" << endl;
	ShuffleData(arr1);
	Sorting(QuickSort);
	cout << "================================================" << endl;

	// Release memory
	delete[] arr1;

	return 0;
}
}