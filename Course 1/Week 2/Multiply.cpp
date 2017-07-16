#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;
int main()
{
    string num1 = "123542141545454545454545454546546545454544548543333334";
    string num2 = "171454654654654545454454854546546545454544548544544545";
    int sum, mul;
    int n1 = num1.size(), n2 = num2.size();
    vector<int> largemul(200,0);
    int a = 0; 
    int b = 0; 
    for (int i=n1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 		b = 0; 
        for (int j=n2-1; j>=0; j--)
        {
            mul = num2[j] - '0';
 		    sum = n1*mul + largemul[a + b] + carry;
 		    carry = sum/10;
 		    largemul[a + b] = sum % 10;
            b++;
        }
        if (carry > 0)
            largemul[a + b] += carry;
 		a++;
    }
 	int i=largemul.size() - 1;
    while(i>=0 && largemul[i] == 0){
    	i--;	
	}
    if (i == -1)
       cout<<"0";
 	string s = "";
    while (i >= 0)
        s = s + to_string(largemul[i--]);
 	cout<<s;
    return 0;
}
