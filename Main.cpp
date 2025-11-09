/******************************************************************

CIS 22C

Lab 4: This program sorts an array in descending order using either
merge sort, quick sort, or insertion sort, which are all recursive.
The type of data that can be sorted are char, int and string. This
program will also write out the screen output onto a file called
output.

Authors: Alexandria Liu
		 Stuart James Granville

Date: 5/18/19

*******************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template< typename T > class Array {
private:
	int size;
public:
	T * myarray;
	Array() {}

	/******************************************************************
	Constructor, which takes user input size

	Pre: s - size of array
	Post: array is dynamically allocated

	*******************************************************************/
	Array(int s) {
		size = s;
		myarray = new T[size];
	}
	/******************************************************************
	This function adds data to an element of the array

	Pre: elem - index of the array
		 val - value that will to be place into the array
	Post: array at elem index will have the value of val

	*******************************************************************/
	void addArray(int elem, T val) {
		myarray[elem] = val;
	}

	/******************************************************************
	This function prints the array

	Pre: there is an array
	Post: prints out each value of the array, separated by commas
		  to console and file

	*******************************************************************/
	void printArray() {
		ofstream out;
		out.open("output.txt", ios::app);
		for (int i = 0; i < size; i++) {
			if (i + 1 == size) {
				cout << myarray[i] << endl;
				out << myarray[i] << endl;
			}
			else {
				cout << myarray[i] << ", ";
				out << myarray[i] << ", ";
			}
		}
		out.close();
	}
};

/******************************************************************
This funciton sorts the array in descending order by using insertion.

Pre: a - object of the class Array of type T
	 n - size of the array
Post: the array is sorted in descending order

*******************************************************************/
template< typename T > void recurInsertionSort(Array<T> a, int n);

/******************************************************************
This funciton sorts the array in descending order by using quick sort.

Pre: a - object of the class Array of type T
	 low - index of the lower end of the array
	 high - index of the higher end of the array
Post: the array is sorted in descending order

*******************************************************************/
template< typename T > void recurQuickSort(Array<T> a, int low, int high);


/******************************************************************
This funciton swaps one element on the lower end of the array with
another element on the higher end of the array if the current
element is larger than or equal to pivot.

Pre: a - object of the class Array of type T
	 low - index of the lower end of the array
	 high - index of the higher end of the array
Post:
Return: next index number

*******************************************************************/
template< typename T > int partition(Array<T> a, int low, int high);

/******************************************************************
This funciton swaps two values.

Pre: a - any type of value
	 b - any type of value but it is the same as a
Post: the two values have been swap

*******************************************************************/
template< typename T > void swap(T* a, T* b);

/******************************************************************
This funciton sorts the array in descending order by using merge sort.

Pre: a - object of the class Array of type T
	 l - index number on the left side of the array
	 r - index number on the right side of the array
Post: the array is sorted in descending order

*******************************************************************/
template< typename T > void recurMergeSort(Array<T> a, int l, int r);

/******************************************************************
This funciton makes two temp array, dividing the array in half, and
compares them. It then merges the two arrays back together into one.

Pre: a - object of the class Array of type T
	 l - index of the left side of the array
	 m - index of the start of the middle of the array
	 r - index of the right side of the array
Post: Merges two subarrays of myarray[]

*******************************************************************/
template< typename T > void merge(Array<T> a, int l, int m, int r);


int main() {

	ofstream out;
	out.open("output.txt");
	const int SORT_MAX_SIZE = 32;
	int size = 0;
	int intTemp;
	string stringTemp;
	char charTemp;
	char typeChoice;
	char sortChoice;

	do {
		cout << "Choose a type for the array.\na) int\nb) string\nc) char\nq) Quit" << endl;
		out << "Choose a type for the array.\na) int\nb) string\nc) char\nq) Quit" << endl;
		cin >> typeChoice;
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl;
		out << typeChoice << endl << endl;

		if (typeChoice != 'q' && (typeChoice == 'a' || typeChoice == 'b' || typeChoice == 'c')) {
			do {
				cout << "Enter a size for your new array not to exceed 32." << endl;
				out << "Enter a size for your new array not to exceed 32." << endl;
				cin >> size;
				out << size << endl;
				while (!cin.good())
				{
					cout << "Enter a numerical size." << endl;
					out << "Enter a numerical size." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cin >> size;
					out << size << endl;
				}
				if (size > 32) {
					cout << "Size exceeds SORT_MAX_SIZE limit of 32." << endl;
					out << "Size exceeds SORT_MAX_SIZE limit of 32." << endl;
				}
				else if (size <= 0) {
					cout << "Size cannot be lower than or equal to 0." << endl;
					out << "Size exceeds SORT_MAX_SIZE limit of 32." << endl;
				}
			} while (size > 32 || size <= 0);
		}

		Array<int> intArray(size);
		Array<string> stringArray(size);
		Array<char> charArray(size);
		switch (typeChoice) {
		case 'a':
			do {
				cout << "\nChoose a sorting option.\na) Insertion Sort\nb) Quick Sort\nc) Merge Sort\nq) Return to type selection menu" << endl;
				out << "\nChoose a sorting option.\na) Insertion Sort\nb) Quick Sort\nc) Merge Sort\nq) Return to type selection menu" << endl;
				cin >> sortChoice;
				cin.clear();
				cin.ignore(256, '\n');
				cout << endl;
				out << sortChoice << endl << endl;

				switch (sortChoice) {
				case 'a': // Insertion Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						cin >> intTemp;
						out << intTemp << endl;
						while (!cin.good())
						{
							cout << "Enter a numerical value for element " << i << ": ";
							out << "Enter a numerical value for element " << i << ": ";
							cin.clear();
							cin.ignore(256, '\n');
							cin >> intTemp;
							out << intTemp << endl;
						}
						intArray.addArray(i, intTemp);
					}

					cout << "\nArray of integers sorted in descending order using Insertion Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of integers sorted in descending order using Insertion Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					intArray.printArray();
					recurInsertionSort(intArray, size);
					out.open("output.txt", ios::app);

					break;
				case 'b': // Quick Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						cin >> intTemp;
						out << intTemp << endl;
						while (!cin.good())
						{
							cout << "Enter a numerical value for element " << i << ": ";
							out << "Enter a numerical value for element " << i << ": ";
							cin.clear();
							cin.ignore(256, '\n');
							cin >> intTemp;
							out << intTemp << endl;
						}
						intArray.addArray(i, intTemp);
					}

					cout << "\nArray of integers sorted in descending order using Quick Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of integers sorted in descending order using Quick Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					intArray.printArray();
					recurQuickSort(intArray, 0, size - 1);
					out.open("output.txt", ios::app);

					break;
				case 'c': // Merge Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						cin >> intTemp;
						out << intTemp << endl;
						while (!cin.good())
						{
							cout << "Enter a numerical value for element " << i << ": ";
							out << "Enter a numerical value for element " << i << ": ";
							cin.clear();
							cin.ignore(256, '\n');
							cin >> intTemp;
							out << intTemp << endl;
						}
						intArray.addArray(i, intTemp);
					}

					cout << "\nArray of integers sorted in descending order using Merge Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of integers sorted in descending order using Merge Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					intArray.printArray();
					recurMergeSort(intArray, 0, size - 1);
					out.open("output.txt", ios::app);

					break;
				case 'q':
					break;
				default:
					cout << "You did not select an option." << endl;
					out << "You did not select an option." << endl;
					break;
				}
			} while (sortChoice != 'q');
			break;
		case 'b':
			do {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\nChoose a sorting option.\na) Insertion Sort\nb) Quick Sort\nc) Merge Sort\nq) Return to type selection menu" << endl;
				out << "\nChoose a sorting option.\na) Insertion Sort\nb) Quick Sort\nc) Merge Sort\nq) Return to type selection menu" << endl;
				cin >> sortChoice;
				cin.clear();
				cin.ignore(256, '\n');
				cout << endl;
				out << sortChoice << endl << endl;

				switch (sortChoice) {
				case 'a': // Insertion Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						getline(cin, stringTemp);
						out << stringTemp << endl;
						stringArray.addArray(i, stringTemp);
					}

					cout << "\nArray of strings sorted in descending order using Insertion Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of strings sorted in descending order using Insertion Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					stringArray.printArray();
					recurInsertionSort(stringArray, size);
					out.open("output.txt", ios::app);

					break;
				case 'b': // Quick Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						getline(cin, stringTemp);
						out << stringTemp << endl;
						stringArray.addArray(i, stringTemp);
					}

					cout << "\nArray of strings sorted in descending order using Quick Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of strings sorted in descending order using Quick Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					stringArray.printArray();
					recurQuickSort(stringArray, 0, size - 1);
					out.open("output.txt", ios::app);

					break;
				case 'c': // Merge Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						getline(cin, stringTemp);
						out << stringTemp << endl;
						stringArray.addArray(i, stringTemp);
					}

					cout << "\nArray of strings sorted in descending order using Merge Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of strings sorted in descending order using Merge Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					stringArray.printArray();
					recurMergeSort(stringArray, 0, size - 1);
					out.open("output.txt", ios::app);

					break;
				case 'q':
					break;
				default:
					cout << "You did not select an option." << endl;
					out << "You did not select an option." << endl;
					break;
				}
			} while (sortChoice != 'q');
			break;
		case 'c':
			do {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\nChoose a sorting option.\na) Insertion Sort\nb) Quick Sort\nc) Merge Sort\nq) Return to type selection menu" << endl;
				out << "\nChoose a sorting option.\na) Insertion Sort\nb) Quick Sort\nc) Merge Sort\nq) Return to type selection menu" << endl;
				cin >> sortChoice;
				cin.clear();
				cin.ignore(256, '\n');
				cout << endl;
				out << sortChoice << endl << endl;

				switch (sortChoice) {
				case 'a': // Insertion Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						cin >> charTemp;
						out << charTemp << endl;
						charArray.addArray(i, charTemp);
					}

					cout << "\nArray of characters sorted in descending order using Insertion Sort (first line is pre-pass, last is sorted)" << endl;
					out << "\nArray of characters sorted in descending order using Insertion Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					charArray.printArray();
					recurInsertionSort(charArray, size);
					out.open("output.txt", ios::app);

					break;
				case 'b': // Quick Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						cin >> charTemp;
						out << charTemp << endl;
						charArray.addArray(i, charTemp);
					}

					cout << "Array of characters sorted in descending order using Quick Sort (first line is pre-pass, last is sorted)" << endl;
					out << "Array of characters sorted in descending order using Quick Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					charArray.printArray();
					recurQuickSort(charArray, 0, size - 1);
					out.open("output.txt", ios::app);

					break;
				case 'c': // Merge Sort
					for (int i = 0; i < size; i++) {
						cout << "Enter a value for array element " << i << ": ";
						out << "Enter a value for array element " << i << ": ";
						cin >> charTemp;
						out << charTemp << endl;
						charArray.addArray(i, charTemp);
					}

					cout << "Array of characters sorted in descending order using Merge Sort (first line is pre-pass, last is sorted)" << endl;
					out << "Array of characters sorted in descending order using Merge Sort (first line is pre-pass, last is sorted)" << endl;
					out.close();
					charArray.printArray();
					recurMergeSort(charArray, 0, size - 1);
					out.open("output.txt", ios::app);

					break;
				case 'q':
					break;
				default:
					cout << "You did not select an option." << endl;
					out << "You did not select an option." << endl;
					break;
				}
			} while (sortChoice != 'q');
		case 'q':
			break;
		default:
			cout << "You did not select an option." << endl;
			out << "You did not select an option." << endl;
			break;
		}
	} while (typeChoice != 'q');

	out.close();
	system("pause");
	return 0;
}

/******************************************************************
if there is only one element in the array (or less)
return

Sort the first n-1 elements

while n - 2 > 0 and the value store at the element n - 2 is less than the n - 1 element value
swap the values of the elements in n - 2 and n - 1

print array

*******************************************************************/
template< typename T > void recurInsertionSort(Array<T> a, int n)
{
	if (n <= 1) {
		return;
	}

	// Sort first n-1 elements 
	recurInsertionSort(a, n - 1);

	// Insert last element at its correct position in sorted array. 
	T last = a.myarray[n - 1];
	int j = n - 2;

	//Move the elements if the array below is less than the last element
	while (j >= 0 && a.myarray[j] < last)
	{
		a.myarray[j + 1] = a.myarray[j];
		j--;
	}
	a.myarray[j + 1] = last;
	
	a.printArray();
}

/******************************************************************
if the lower index is less than the higher index
get partition index

sort the elements before the partition
sort the elements after the partition

print array

*******************************************************************/
template< typename T > void recurQuickSort(Array<T> a, int low, int high)
{
	if (low < high)
	{
		// pi is partitioning index
		int pi = partition(a, low, high);

		// Separately sort elements before partition and after partition
		recurQuickSort(a, low, pi - 1);
		recurQuickSort(a, pi + 1, high);
	}

	a.printArray();
}


/******************************************************************
privot value = the value of the high index
index of the smaller element

go through all the elements within the low and high index
if the currenct element is larger or equal to pivot
swap the smaller element with the current element

swap the element at one index higher of the smaller element with the element with the high index
return index of the one higher than the smaller element index
*******************************************************************/
template< typename T > int partition(Array<T> a, int low, int high)
{
	T pivot = a.myarray[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is larger than or equal to pivot 
		if (a.myarray[j] >= pivot)
		{
			i++;    // increment index of smaller element 
			swap(&a.myarray[i], &a.myarray[j]);
		}
	}
	swap(&a.myarray[i + 1], &a.myarray[high]);
	return (i + 1);
}

/******************************************************************
temp = a
a = b
b = temp

*******************************************************************/
template< typename T > void swap(T* a, T* b)
{
	T t = *a;
	*a = *b;
	*b = t;
}

/******************************************************************
if left index is less than right index
find middle index between the two

sort first half
sort second half

merge the two half together

print array

*******************************************************************/
template< typename T > void recurMergeSort(Array<T> a, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		recurMergeSort(a, l, m);
		recurMergeSort(a, m + 1, r);

		merge(a, l, m, r);
	}
	a.printArray();
}

/******************************************************************
two temp arrays one containing the left side of the array and the other with the right side

go through the arrays
if the left side value is greater than or equal to the right side
put the left temp array value into the original array
else
put the right temp array value into the original array

copy whatever is left in the temp arrays into the original array

*******************************************************************/
template< typename T > void merge(Array<T> a, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	//temp arrays
	Array<T> L(n1);
	Array<T> R(n2);

	//Copy data to temp arrays
	for (i = 0; i < n1; i++)
		L.myarray[i] = a.myarray[l + i];
	for (j = 0; j < n2; j++)
		R.myarray[j] = a.myarray[m + 1 + j];

	//Merge the temp arrays back 
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L.myarray[i] >= R.myarray[j])
		{
			a.myarray[k] = L.myarray[i];
			i++;
		}
		else
		{
			a.myarray[k] = R.myarray[j];
			j++;
		}
		k++;
	}

	//Copy the remaining elements of L[]
	while (i < n1)
	{
		a.myarray[k] = L.myarray[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[]
	while (j < n2)
	{
		a.myarray[k] = R.myarray[j];
		j++;
		k++;
	}
}