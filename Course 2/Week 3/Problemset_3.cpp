#include<bits/stdc++.h>
using namespace std;
int get_mid(priority_queue < int > & p1, priority_queue < int, vector < int > , greater < int > > & p0, int element, int median);
int main() 
{
    priority_queue < int > p1;
    long sum = 0;
    priority_queue < int, vector < int > , greater < int > > p0;
    FILE * fp = freopen("Median.txt", "r", stdin);
    int i, med = 0;
    while (scanf("%d", & i) > 0) 
	{
        med = get_mid(p1, p0, i, med);
        sum = sum + med;
    }
    fclose(fp);
    int modulo = sum % 10000;
    cout << "Sum of the 10000 medians, modulo 10000: " << modulo;
    return 0;
}
int get_mid(priority_queue < int > & p1, priority_queue < int, vector < int > , greater < int > > & p0, int element, int median) {

    if (p1.size() == p0.size()) 
	{
        if (element < median) 
		{
            p1.push(element);
            median = p1.top();
        } 
		else 
		{
            p0.push(element);
            median = p0.top();
        }
    } 
	else if (p1.size() > p0.size()) 
	{
        if (element < median) 
		{	
            p0.push(p1.top());
            p1.pop();
            p1.push(element);
        } 
		else 
		{
            p0.push(element);
        }
        median = p1.top();
    } 
	else 
	{
        if (element < median) 
		{
            p1.push(element);

        } 
		else 
		{
            p1.push(p0.top());
            p0.pop();
            p0.push(element);
        }
        median = p1.top();
    }
    return median;
}

