#include <vector>
#include <iostream>

using namespace std;

struct result { int profit, buy, sell, index; };

int DPBottomUp(vector<int> A, int index, int minPrice, int profit, int* buy, int *sell)
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

    return max(profit, DPBottomUp(A, index+1, minPrice, profit, buy, sell));
}

result Task3B(vector<vector<int> > A, int m, int n)
{
    result r1;
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for(int i = 0; i < m; i++)
    {
        int result = DPBottomUp(A[i], 1, A[i][0], 0, &buy, &sell);
        if(result > profit)
        {
            profit = result;
            index = i;
        }
    }

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

    result res = Task3B(A, m, n);
    cout << "Profit :" <<res.profit <<endl << "Stock No: " << res.index <<endl << "Buy: " << res.buy <<endl << "Sell:" << res.sell <<endl;
}