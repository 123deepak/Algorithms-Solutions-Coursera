# include <iostream>
# include <fstream>
# include <vector>
using namespace std;
int partition(vector<int>& num, int low, int high) {
	int pivot = num[low];
	int i = low + 1;
	int j;
	for (j = low + 1; j <= high; ++j) {
		if (num[j] < pivot) {
			swap(num[j], num[i]);
			++i;
		}
	}
	swap(num[low], num[i-1]);
	return (i - 1);
}
long quicksort(vector<int>& num, int low, int high) {
	int left, right, pivot;
	if (high <= low)
		return 0;
	int change = num[low];
	num[low]= num[high];
	num[high]=change;
	pivot = partition(num, low, high);
	left = quicksort(num, low, pivot-1);
	right = quicksort(num, pivot+1, high);
	return (left + right + (high - low));
}
int main(int argc, char** argv) 
{
	vector<int> num;
	ifstream input;
	input.open("QuickSort.txt", ios::in);
	int tmp;
	while (input >> tmp) {
		num.push_back(tmp);
	}
	cout<< quicksort(num, 0, num.size()-1);
	input.close();
	return 0;
}



