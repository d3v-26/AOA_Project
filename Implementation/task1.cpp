#include <vector>
#include <iostream>

using namespace std;

struct result { int profit, buy, sell; };
struct result2 { int profit, buy, sell, index; };

result SingleMaxProfit(vector<int> A, int n) 
{ 
    result r;
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
    r.profit = profit;
    r.buy = buy;
    r.sell = sell;
    return r;
}

result2 Task1(vector<vector<int> > A, int m, int n) {
    
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for (int i = 0; i < m; i++) 
    {
        result r = SingleMaxProfit(A[i], n);
        if(r.profit > profit) 
        {
            profit = r.profit;
            buy = r.buy;
            sell = r.sell;
            index = i;
        }
    }
    result2 r1;
    r1.profit = profit;
    r1.buy = buy;
    r1.sell = sell;
    r1.index = index;

    return r1;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int> > A(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }

    result2 result = Task1(A, m, n);
    cout << "Profit :" <<result.profit <<endl << "Stock No: " << result.index <<endl << "Buy: " << result.buy <<endl << "Sell:" << result.sell <<endl;
}