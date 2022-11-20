#include "tasks.h"

// /**
//  * Structure that describes a Transaction
//  * 
//  * @param stock  int - Index of the stock that corresponds to this Transaction.
//  * @param profit int - Profit of the Transaction.
//  * @param buy    int - Index of the `Day` that we `buy` the stock `stock`
//  * @param sell   int - Index of the `Day` that we `sell` the stock `stock`
//  */
// struct transaction
// {
//     int stock, profit, buy, sell;
// };

/**
 *   Iterative Algorithm to to Calculate the transaction that yields max profit in given Stock.
 *   Calculates and returns a Single Transaction that is Maximum for given Stock. Time complexity is in Order on n.
 *
 *   @param   A          vector<int>  - Vector containing prices of a stock
 *   @param   n          int          - Number of days
 *   @returns            Transaction  - A single transaction with Max profit
 */
transaction DPBottomUp(vector<int> A, int n)
{
    int profit = 0, buy = 0, sell = 0; // Variable to keep track of max profit
    
    int *dp = new int[n];       // This array maintains to the date what is the min stock price
    int *buyarr = new int[n];   // This array maintains the index of the min stock price to the date
    
    dp[0] = A[0];               // Base case i.e. first date price is min on the first date
    buyarr[0] = 0;              // Base case i.e. index of the min first date price
    
    for(int i = 1; i < n; i++)  // Following `for` loop computes the min stock price to the date array
    {
        if(A[i] < dp[i-1])      // If current price is lower than all that were encountered than update price at current day
        {
            dp[i] = A[i];
            buyarr[i] = i;      // Store its index
        }
        else
        {
            dp[i] = dp[i-1];            // Otherwise fetch the previous values
            buyarr[i] = buyarr[i-1];    // And its index
        }
    }

    for(int i = 0; i < n; i++)  // Following `for` loop computes max profit using dp array
    {
        int currentProfit = A[i] - dp[i];   // Compute current profit i.e. Current price - Min price so far
        if(profit < currentProfit)          // If current profit is greater than any transaction computed than update max profit
        {
            sell = i;
            profit = currentProfit;
            buy = buyarr[i];
        }
    }
    
    return transaction { -1, profit, buy, sell }; // Return the transaction that yields the Max profit.
}

/**
 *   Task 3B of the programming project. Its time complexity is in order of m*n.
 *   Computes and return a Single transaction that is maximum for given stocks m and given days n.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @return   transaction         - A single transaction that has most profit
 */
transaction Task3B(vector<vector<int>> A, int m, int n)
{
    int profit = 0, buy = 0, sell = 0, stock = 0; // Variables to keep track of max profit.
    for(int i = 0; i < m; i++)                    // Iterating over `m` stocks
    {
        transaction result = DPBottomUp(A[i], n); // Computing max profit for current stock
        if(result.profit > profit)                // Updating the Max profit
        {
            profit = result.profit;
            buy = result.buy;
            sell = result.sell;
            stock = i;
        }
    }

    return transaction {stock, profit, buy, sell};  // Return the transaction that yields the Max profit.
}

// // Main method
// int main() 
// {
//     /**
//      *  Get the inputs `m`, `n` & `A` which are specified as below:
//      *  m, n - First line contains two integers m & n separated by a single space.
//      *  A    - Next m lines each contains of n integers (prices for n days) separated by a single space.
//      */
//     int m, n;
//     cin >> m >> n;

//     vector<vector<int>> A(m, vector<int> (n, 0));
//     for (int i = 0; i < m; i++) 
//     {
//         for (int j = 0; j < n; j++) 
//         {
//             cin >> A[i][j];
//         }
//     }

//     transaction result = Task3B(A, m, n); // Get the result of Task3B
    
//     // Print the output as a single line with three integers (Stock, BuyDay, SellDay) separated by a single space.
//     cout << result.stock << " " << result.buy << " " << result.sell << endl; 
// }