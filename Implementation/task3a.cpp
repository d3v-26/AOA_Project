#include <bits/stdc++.h>

using namespace std;

auto DPMemoization(vector<int> A, int n)
{
    struct result { int profit, buy, sell; };
    
    int profit = 0, buy = 0, sell = 0;
    
    int *dp = new int[n];       // This array maintains to the date what is the min stock price
    int *buyarr = new int[n];   // This array maintains the index of the min stock price to the date
    
    dp[0] = A[0];   // Base case i.e. first date price is min on the first date
    buyarr[0] = 0;  // Base case i.e. index of the min first date price
    
    for(int i = 1; i < n; i++)  // Following `for` loop computes the min stock price to the date array
    {
        if(A[i] < dp[i-1])
        {
            dp[i] = A[i];
            buyarr[i] = i;
        }
        else
        {
            dp[i] = dp[i-1];
            buyarr[i] = buyarr[i-1];
        }
    }

    for(int i = 0; i < n; i++)  // Following `for` loop computes max profit using dp array
    {
        int currentProfit = A[i] - dp[i];
        if(profit < currentProfit)
        {
            sell = i;
            profit = currentProfit;
            buy = buyarr[i];
        }
    }
    
    return result { profit, buy, sell };
}

auto Task3A(vector<vector<int>> A, int m, int n)
{
    struct result { int profit, buy, sell, index; };
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for(int i = 0; i < m; i++)
    {
        auto result = DPMemoization(A[i], n);
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

    auto result = Task3A(A, m, n);
    cout << result.index << " " << result.buy << " " << result.sell << endl;
}