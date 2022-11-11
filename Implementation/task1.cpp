#include <bits/stdc++.h>

using namespace std;

auto SingleMaxProfit(vector<int> A, int n) 
{ 
    struct result { int profit, buy, sell; };
    int profit = 0;
    int buy = 0, sell = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            int currentProfit = A[j] - A[i];
            if (currentProfit > profit)
            {
                profit = currentProfit;
                buy = i;
                sell = j;                
            }
        }
    }

    return result {profit, buy, sell};
}

auto Task1(vector<vector<int>> A, int m, int n) {
    struct result { int profit, buy, sell, index; };
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for (int i = 0; i < m; i++) 
    {
        auto result = SingleMaxProfit(A[i], n);
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

    auto result = Task1(A, m, n);
    cout << result.index << " " << result.buy << " " << result.sell << endl;
}