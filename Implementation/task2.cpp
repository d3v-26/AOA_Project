#include <bits/stdc++.h>

using namespace std;

auto GreedySingleMaxProfit(vector<int> A, int n)
{
    struct result { int profit, buy, sell; };
    int leastSoFar = 10000;
    int profit = 0;
    int currentProfit = 0;
    int buy = 0, sell = 0, minIndex = 0;

    for(int i = 0; i < n; i++)
    {
        if(A[i] < leastSoFar)
        {
            leastSoFar = A[i];
            minIndex = i;
        }
        currentProfit = A[i] - leastSoFar;
        if(currentProfit > profit)
        {
            profit = currentProfit;
            buy = minIndex;
            sell = i;
        }
    }

    return result {profit, buy, sell};
}

auto Task2(vector<vector<int>> A, int m, int n)
{
    struct result { int profit, buy, sell, index; };
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for(int i = 0; i < m; i++)
    {
        auto result = GreedySingleMaxProfit(A[i], n);
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

    auto result = Task2(A, m, n);
    cout << result.index << " " << result.buy << " " << result.sell << endl;
}

    