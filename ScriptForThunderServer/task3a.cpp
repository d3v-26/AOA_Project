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
 *   Recursive Algorithm to populate Min Value of a given stock to vector DP with its index being populated at BuyInx.
 *   Computes Min Values of a given stock at a given date and stores the result in Vectors DP & BuyInx.
 *
 *   @param  DP         vector<int>& - Reference Vector that will be populared by Min Values of prices for a given date
 *   @param  BuyInx     vector<int>& - Reference Vector that will be populared by index of those Min Values for a given date
 *   @param  A          vector<int>  - Vector containing prices of a stock
 *   @param  index      int          - Current Index
 */
void initDP(vector<int> &DP, vector<int> &BuyInx, vector<int> A, int index)
{
    if(index < 0) return;                   // if current index is less than 0 just return
    if(index == 0)                          // If current index is 0 populate the 0th indices of DP and BuyInx
    {
        DP[0] = A[0];
        BuyInx[0] = 0;
        return;                             // then return
    }
    initDP(DP, BuyInx, A, index-1);         // Compute DP and BuyInx for previous index
    if(A[index] < DP[index-1])              // After computing DP at previous index check if current price is less than what is yet encountered
    {                                       // If that is the case than Store the new Min value and its index
        DP[index] = A[index];
        BuyInx[index] = index;
    }
    else
    {                                       // else use the value computed at previous index
        DP[index] = DP[index-1];
        BuyInx[index] = BuyInx[index-1];
    }
}

/**
 *   Recursive implementation of ALG3 using Memoization that has time complexity in order of n.
 *   Computes and returns  maximum profit for the given stock for given index.
 *
 *   @param  A          vector<int> - Vector containing prices of a stock
 *   @param  DP         vector<int> - Vector that consists of Min Values for a given date
 *   @param  BuyInx     vector<int> - Vector that consists of index of those Min Values for a given date
 *   @param  profit     int         - Variable that stores Max Profit encountered till date
 *   @param  buy        int*        - Reference variable where we store index of buy day
 *   @param  sell       int*        - Reference variable where we store index of sell day
 *   @returns           int         - Max Profit for given stock
 */
int DPMemoization(vector<int> A, vector<int> DP, vector<int> BuyInx, int index, int profit, int* buy, int *sell)
{
    // If the index is not in range of length of A, return the max profit encountered till date
    if( index >= A.size() || index <= 0)
    {
        return profit;
    }

    // Compute the Profit for previous index.
    profit = DPMemoization(A, DP, BuyInx, index-1, profit, buy, sell);
    
    // Compute Current Profit i.e. Price at current index - Min price encountered till date
    int currentProfit = A[index] - DP[index];
    
    // if currentProfit is greater than the profit at previous index than update currentProfit and store the buy and sell index.
    if(profit < currentProfit)
    {
        profit = currentProfit;
        *sell = index;
        *buy = BuyInx[index];
    }

    // return max profit
    return profit;
}

/**
 *   Task 3A of the project. Time Complexity is in order of m*n.
 *   Computes and returns a transaction that yields maximum profit for all given stocks.
 *   It is the implementation of ALG3 of the programming project.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @return   transaction         - A single transaction that has most profit
 */
transaction Task3A(vector<vector<int>> A, int m, int n)
{
    int profit = 0, buy = 0, sell = 0, stock = 0;                           // Variables to keep track of Max Profit
    vector<int> DP(n, 0);
    vector<int> BuyInx(n, 0);
    for(int i = 0; i < m; i++)                                              // Iterate over all stocks
    {
        initDP(DP, BuyInx, A[i], n-1);                                      // Calling InitDP to populate DP and BuyInx
        int cbuy = 0, csell = 0;   
        int result = DPMemoization(A[i], DP, BuyInx, n-1, 0, &cbuy, &csell);       // Get Max Transaction in each stock
        if(result > profit)                                                        // Store the Max transaction encountered till now
        {
            profit = result;
            stock = i;
            buy = cbuy;
            sell = csell;
        }
    }

    return transaction {stock, profit, buy, sell};                          // Return the transaction that has Max profit for all `m` stocks
}

// // Main method
// int main() 
// {
//     /**
//      *  Get the inputs `m`, `n` & `A` which are specified as below:
//      *  m, n - First line contains two integers m & n separated by a single space
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

//     transaction result = Task3A(A, m, n); // Get the result of Task3A
    
//     // Print the output as a single line with three integers (Stock, BuyDay, SellDay) separated by a single space.
//     cout << result.stock << " " << result.buy << " " << result.sell << endl; 
// }