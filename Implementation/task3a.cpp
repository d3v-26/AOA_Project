#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

struct result
{
    int profit, buy, sell;
};
struct result2
{
    int profit, buy, sell, index;
};

result DPMemoization(vector<int> A, int n)
{
    result r;
    int profit = 0, buy = 0, sell = 0;

    int *dp = new int[n];     // This array maintains to the date what is the min stock price
    int *buyarr = new int[n]; // This array maintains the index of the min stock price to the date

    dp[0] = A[0];  // Base case i.e. first date price is min on the first date
    buyarr[0] = 0; // Base case i.e. index of the min first date price

    for (int i = 1; i < n; i++) // Following `for` loop computes the min stock price to the date array
    {
        if (A[i] <= dp[i - 1])
        {
            dp[i] = A[i];
            buyarr[i] = i;
        }
        else
        {
            dp[i] = dp[i - 1];
            buyarr[i] = buyarr[i - 1];
        }
    }

    for (int i = 0; i < n; i++) // Following `for` loop computes max profit using dp array
    {
        int currentProfit = A[i] - dp[i];
        if (profit <= currentProfit)
        {
            sell = i;
            profit = currentProfit;
            buy = buyarr[i];
        }
    }

    r.profit = profit;
    r.buy = buy;
    r.sell = sell;
    return r;
}

result2 Task3A(vector<vector<int>> A, int m, int n)
{
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for (int i = 0; i < m; i++)
    {
        result r = DPMemoization(A[i], n);
        if (r.profit >= profit)
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
    // result2 res = Task3A(A, m, n);
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
    result2 result = Task3A(A, m, n);
    t = clock() - t;
    cout << "Time Elapsed : " << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Profit :" << result.profit << endl
         << "Stock No: " << result.index << endl
         << "Buy: " << result.buy << endl
         << "Sell:" << result.sell << endl;
}