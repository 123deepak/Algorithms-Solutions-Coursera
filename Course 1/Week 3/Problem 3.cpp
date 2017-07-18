# include <iostream>
# include <fstream>
# include <vector>
using namespace std;

void swap(int *x, int *y)
{
     int temp=*x;
     *x=*y;
     *y=temp;
}
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
	int m=low+(high-low)/2;
    if((num[low]>=num[m] && num[low]>=num[high]) && (num[m]>=num[high]) )
        swap(&num[m], &num[low]); 
    else if((num[low]>=num[m] && num[low]>=num[high]) && (num[m]<=num[high]))
    	swap(&num[high],&num[low]);
    else if((num[m]>=num[low] && num[m]>=num[high]) && (num[high]>=num[low]))
        swap(&num[high], &num[low]);
    else if((num[high]>=num[m] && num[high]>=num[low]) && (num[m]>=num[low]) )
        swap(&num[m], &num[low]);
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



