#include <bits/stdc++.h>

using namespace std;

auto DPBottomUp(vector<int> A, int n)
{
    struct result { int profit, buy, sell; };
    
    int profit = 0, buy = 0, sell = 0;
    int min = A[0];

    for(int i = 1; i < n; i++)
    {
        int currentProfit = A[i] - min;
        if(profit < currentProfit)
        {
            sell = i;
            profit = currentProfit;
        }
        if(A[i] < min)
        {
            min = A[i];
            buy = i;
        }
    }
    
    return result { profit, buy, sell };
}

auto Task3B(vector<vector<int>> A, int m, int n)
{
    struct result { int profit, buy, sell, index; };
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for(int i = 0; i < m; i++)
    {
        auto result = DPBottomUp(A[i], n);
        if(result.profit > profit)
        {
            profit = result.profit;
            buy = result.buy;
            sell = result.sell;
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

    auto result = Task3B(A, m, n);
    cout << result.index << " " << result.buy << " " << result.sell << endl;
}