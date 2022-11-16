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

result GreedySingleMaxProfit(vector<int> A, int n)
{
    result r;
    int leastSoFar = 10000;
    int profit = 0;
    int currentProfit = 0;
    int buy = 0, sell = 0, minIndex = 0;

    for (int i = 0; i < n; i++)
    {
        if (A[i] <= leastSoFar)
        {
            leastSoFar = A[i];
            minIndex = i;
        }
        currentProfit = A[i] - leastSoFar;
        if (currentProfit >= profit)
        {
            profit = currentProfit;
            buy = minIndex;
            sell = i;
        }
    }

    r.profit = profit;
    r.buy = buy;
    r.sell = sell;
    return r;
}

result2 Task2(vector<vector<int>> A, int m, int n)
{
    int profit = 0;
    int buy = 0, sell = 0, index = 0;
    for (int i = 0; i < m; i++)
    {
        result r = GreedySingleMaxProfit(A[i], n);
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
    // result2 res = Task2(A, m, n);
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
    result2 result = Task2(A, m, n);
    t = clock() - t;
    cout << "Time Elapsed : " << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Profit :" << result.profit << endl
         << "Stock No: " << result.index << endl
         << "Buy: " << result.buy << endl
         << "Sell:" << result.sell << endl;
}
