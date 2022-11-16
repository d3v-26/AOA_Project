#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

struct result
{
    int profit, buy, sell, index;
};

int DPBottomUp(vector<int> A, int index, int minPrice, int profit, int *buy, int *sell)
{
    if (index >= A.size() || index < 0)
    {
        return profit;
    }
    int currentProfit = A[index] - minPrice;
    if (profit <= currentProfit)
    {
        *sell = index;
        profit = currentProfit;
    }

    if (minPrice >= A[index])
    {
        minPrice = A[index];
        *buy = index;
    }

    return max(profit, DPBottomUp(A, index + 1, minPrice, profit, buy, sell));
}

result Task3B(vector<vector<int>> A, int m, int n)
{
    result r1;
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for (int i = 0; i < m; i++)
    {
        int result = DPBottomUp(A[i], 1, A[i][0], 0, &buy, &sell);
        if (result >= profit)
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

int main()
{
    int m, n;

    // COMPARISON TASK
    // vector<vector<int> > A;
    // cout << "Name of file: ";
    // string name;
    // cin >> name;
    // std::ifstream infile("../TestCases/TestCase" + name + ".txt");
    // string line;
    // int count = 0;
    // while (std::getline(infile, line))
    // {
    //     std::istringstream iss(line);
    //     if (count < 1)
    //     {
    //         iss >> m >> n;
    //         cout << "M: " << m << endl;
    //         cout << "N: " << n << endl;
    //     }
    //     for (int i = 0; i < m; i++)
    //     {
    //         vector<int> temp;
    //         for (int j = 0; j < n; j++)
    //         {
    //             int k = 0;
    //             infile >> k;
    //             temp.push_back(k);
    //         }
    //         A.push_back(temp);
    //     }
    //     count++;
    // }
    // clock_t t;
    // t = clock();
    // t = clock() - t;
    // result res = Task3B(A, m, n);
    // t = clock() - t;
    // cout << "Time Elapsed : " << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
    // cout << "Profit :" << res.profit << endl
    //      << "Stock No: " << res.index << endl
    //      << "Buy: " << res.buy << endl
    //      << "Sell:" << res.sell << endl;
    // cout << endl
    //      << endl;

    cin >> m >> n;
    vector<vector<int>> A(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }
    clock_t t;
    int f;
    t = clock();
    t = clock() - t;
    result res = Task3B(A, m, n);
    t = clock() - t;
    cout << "Time Elapsed : " << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Profit :" << res.profit << endl
         << "Stock No: " << res.index << endl
         << "Buy: " << res.buy << endl
         << "Sell:" << res.sell << endl;
}