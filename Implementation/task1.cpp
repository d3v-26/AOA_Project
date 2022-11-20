#include <bits/stdc++.h>

using namespace std;

/**
 * Structure that describes a Transaction
 * 
 * @param stock  int - Index of the stock that corresponds to this Transaction.
 * @param profit int - Profit of the Transaction.
 * @param buy    int - Index of the `Day` that we `buy` the stock `stock`
 * @param sell   int - Index of the `Day` that we `sell` the stock `stock`
 */
struct transaction
{
    int stock, profit, buy, sell;
};

/**
 *   Brute Force Algorithm that has time complexity in order of n^2.
 *   Computes and returns a transaction that yields maximum profit for the given stock.
 *
 *   @param  A vector<int> - Vector containing prices of a stock
 *   @param  n int         - Number of Days
 *   @return   transaction - A single transaction that has most profit
 */
transaction BruteForceN2(vector<int> A, int n) 
{ 
    int profit = 0, buy = 0, sell = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            int currentProfit = A[j] - A[i]; // Compute current profit
            if (currentProfit > profit)      // Store the Max profit Till Now
            {
                profit = currentProfit;
                buy = i;
                sell = j;                
            }
        }
    }

    return transaction {-1, profit, buy, sell}; // Return the Max profit as a Transaction
}

/**
 *   Task 1 of the project. Time Complexity is in order of m*n^2.
 *   Computes and returns a transaction that yields maximum profit for all given stocks.
 *   It is the implementation of ALG1 of the programming project.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @return   transaction         - A single transaction that has most profit
 */
transaction Task1(vector<vector<int>> A, int m, int n) 
{
    int profit = 0, buy = 0, sell = 0, stock = 0;       // Variables to keep track of Max Profit
    for (int i = 0; i < m; i++)                         // Iterate over all stocks
    {
        transaction result = BruteForceN2(A[i], n);     // Get Max Transaction in each stock
        if(result.profit > profit)                      // Store the Max transaction encountered till now
        {
            profit = result.profit;
            buy = result.buy;
            sell = result.sell;
            stock = i;
        }
    }

    return transaction {stock, profit, buy, sell};      // Return the transaction that has Max profit for all `m` stocks
}

// Main method
int main() 
{
    /**
     *  Get the inputs `m`, `n` & `A` which are specified as below:
     *  m, n - First line contains two integers m & n separated by a single space.
     *  A    - Next m lines each contains of n integers (prices for n days) separated by a single space.
     */
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

    /**
      * This block of code was written for the comparison task.
      * It takes the file name as input and reads the input from that test case file.
      * It outputs the time taken by the code to run and the output of the test case.
      */

    // string name;
    // cout<<"Enter name: ";
    // cin>>name;
    // ifstream infile;
    // infile.open("../ComparisonTask/TestCases/" + name + ".txt");
    // infile >> m >> n;
    // vector<vector<int>> A(m, vector<int> (n, 0));
    // for (int i = 0; i < m; i++) 
    // {
    //     for (int j = 0; j < n; j++) 
    //     {
    //         infile >> A[i][j];
    //     }
    // }
    // clock_t t;
    // t = clock();
    // transaction result = Task1(A, m, n); // Get the result of Task1
    // t = clock() - t;
    // cout<<(float)t/CLOCKS_PER_SEC<<" seconds"<<endl;
    

    transaction result = Task1(A, m, n); // Get the result of Task1

    // Print the output as a single line with three integers (Stock, BuyDay, SellDay) separated by a single space.
    cout <<result.stock << " " << result.buy << " " << result.sell << endl; 
}