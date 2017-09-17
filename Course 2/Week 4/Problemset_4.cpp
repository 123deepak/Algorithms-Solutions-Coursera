#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
const int MIN = -10000;
const int MAX = 10000;
const char* file = "algo1-programming_prob-2sum.txt";
const int num = 1000000;
int hash[num];
int main()
{
    ifstream f;
    f.open(file);
    for (int i = 0; i < num; i++)
    {
        f >> hash[i];
    }
    sort(hash, hash + num);
    int start = 0;
    int end = num - 1;
    bool array[MAX - MIN + 1];
    for (int i = MIN; i <= MAX; i++)
    {
        array[i - MIN] = false;
    }
    while (start < end)
    {
        int sum = hash[start] + hash[end];
        if (sum < MIN)
        {
            start++;
        }
        else if (sum > MAX)
        {
            end--;
        }
        else
        {
            if (hash[start] != hash[end])
            {
                array[sum - MIN] = true;
            }
            int current_start = start;
            int current_end = end;
            while (true)
            {
                start++;
                int sum = hash[start] + hash[end];
                if (sum < MIN)
                {
                    break;
                }
                else if (sum > MAX)
                {
                    break;
                }
                else
                {
                    if (hash[start] != hash[end])
                    {
                        array[sum - MIN] = true;
                    }
                }
            }
            start = current_start;

            while (true)
            {
                end--;
                int sum = hash[start] + hash[end];
                if (sum < MIN)
                {
                    break;
                }
                else if (sum > MAX)
                {
                    break;
                }
                else
                {
                    if (hash[start] != hash[end])
                    {
                        array[sum - MIN] = true;
                    }
                }
            }
            end = current_end;
            start++;
            end--;
        }
    }
    int count = 0;
    for (int i = MIN; i <= MAX; i++)
    {
        if (array[i - MIN])
        {
            count++;
        }
    }
    cout << count << endl;
    f.close();
    return 0;
}
