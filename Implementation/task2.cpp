#include <bits/stdc++.h>

using namespace std;

// Structure that describes a Transaction
struct transaction
{
    /**
     * @param stock  int - Index of the stock that corresponds to this Transaction.
     * @param profit int - Profit of the Transaction.
     * @param buy    int - Index of the `Day` that we `buy` the stock `stock`
     * @param sell   int - Index of the `Day` that we `sell` the stock `stock`
     */
    int stock, profit, buy, sell;
};

/**
 *   Greedy Algorithm that has time complexity in order of n
 *   Computes and returns a transaction that yields maximum profit for the given stock
 *
 *   @param  A vector<int> - Vector containing prices of a stock
 *   @param  n int         - Number of Days
 *   @return _ transaction - A single transaction that has most profit
 */
transaction GreedySingleMaxProfit(vector<int> A, int n)
{
    int leastSoFar = 10000;                          // leastSoFar keeps track of the least value of price of a stock encountered till the date
    int profit = 0, buy = 0, sell = 0, inx = 0;      // Variables to keep track of Max Profit

    for(int i = 0; i < n; i++)                       // Iterate over the days `n`
    {
        if(A[i] < leastSoFar)                        // If current day has low price that leastSoFar than updated leastSoFar
        {
            leastSoFar = A[i];
            inx = i;                                 // Store the index of lowest price
        }
        int currentProfit = A[i] - leastSoFar;       // Calculate current profit i.e. Current Price - leastSoFar
        if(currentProfit > profit)                   // If Current Profit is greater than every profit encountered so far update profit
        {
            profit = currentProfit;
            sell = i;                                // Store the index of Sell day which has Max profit
            buy = inx;                               // Store the index of buy day which is the index of value that is leastSoFar i.e. inx
        }
    }

    return transaction { -1, profit, buy, sell}; // Return the transaction that has max profit.
}

/**
 *   Task 2 of the project. Time Complexity is in order of m*n.
 *   Computes and returns a transaction that yields maximum profit for all given stocks.
 *   It is the implementation of ALG2 of the programming project.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @return _ transaction         - A single transaction that has most profit
 */
transaction Task2(vector<vector<int>> A, int m, int n)
{
    int profit = 0, buy = 0, sell = 0, stock = 0;               // Variables to keep track of Max Profit
    for (int i = 0; i < m; i++)                                 // Iterate over all stocks
    {
        transaction result = GreedySingleMaxProfit(A[i], n);    // Get Max Transaction in each stock
        if(result.profit > profit)                              // Store the Max transaction encountered till now
        {
            profit = result.profit;
            buy = result.buy;
            sell = result.sell;
            stock = i;
        }
    }

    return transaction {stock, profit, buy, sell};              // Return the transaction that has Max profit for all `m` stocks
}

// Main method
int main() 
{
    /**
     *  Get the inputs `m`, `n` & `A` which are specified as below:
     *  m, n - First line contains two integers m & n separated by a single space
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

    transaction result = Task2(A, m, n); // Get the result of Task2
    
    // Print the output as a single line with three integers (Stock, BuyDay, SellDay) separated by a single space.
    cout << result.stock << " " << result.buy << " " << result.sell << endl; 
}
