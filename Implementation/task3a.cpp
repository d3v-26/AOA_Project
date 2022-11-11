#include <bits/stdc++.h>

using namespace std;

int DPMemoization(vector<int> A, int index, int minPrice, int profit, int* buy, int *sell)
{
    if( index >= A.size() || index < 0)
    {
        return profit;
    }
    int currentProfit = A[index] - minPrice;
    if(profit < currentProfit)
    {
        *sell = index;
        profit = currentProfit;
    }

    if(minPrice > A[index])
    {
        minPrice = A[index];
        *buy = index;
    }

    return max(profit, DPMemoization(A, index+1, minPrice, profit, buy, sell));
}

auto Task3A(vector<vector<int>> A, int m, int n)
{
    struct result { int profit, buy, sell, index; };
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for(int i = 0; i < m; i++)
    {
        int result = DPMemoization(A[i], 1, A[i][0], 0, &buy, &sell);
        if(result > profit)
        {
            profit = result;
            index = i;
        }
    }

    return result {profit, buy, sell, index};
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> A(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }

    auto result = Task3A(A, m, n);
    cout << result.index << " " << result.buy << " " << result.sell << endl;
}