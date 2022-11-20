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
 *   Function to Calculate the sum of profit of the given transactions
 *
 *   @param   T          vector<transaction>  - Vector containing any number of transactions
 *   @returns            int                  - Max profit in all those transactions
 */
int totalProfit(vector<transaction> T)
{
    int profit = 0;             // Variable for keeping track of profit
    for(auto t : T)             // Iterating over all transactions and adding every profit to our profit variable
    {
        profit += t.profit;
    }
    return profit;              // Return the total profit.
}

/**
 *   Function to print all the given transactions
 *
 *   @param   T          vector<transaction>  - Vector containing any number of transactions
 */
void print(vector<transaction> T)
{
    for(auto t : T)
    {
        cout << t.stock << " " << t.profit << " " << t.buy << " " << t.sell << endl;
    }
}

/**
 *   Function to Compare two given transactions.
 *   Returns True if t1 has buy date less than t2 otherwise false.
 *
 *   @param   t1          transaction  - A single transaction
 *   @param   t2          transaction  - A single transaction
 * 
 *   @returns             bool         - boolean variable answering if T1 comes before T2?
 */
bool compare(transaction t1, transaction t2)
{
    if(t1.buy <= t2.buy) return true;
    else return false;
}

/**  
 *   Brute Force Algorithm to Pick atmost k transactions from any given transactions
 *   Recursive Algorithm that Returns atmost k compatible transactions with max profit from given transactions.
 *
 *   @param   T          vector<transaction>  - Vector containing any number of transactions
 *   @param   R          vector<transaction>  - Vector that keeps track of current solution
 *   @param   index      int                  - Variable that keeps track of current index in transactions
 *   @param   k          int                  - Variable that keeps track of number of allowed transactions
 *      
 *   @returns            vector<transaction>  - Vector consisting of atmost k transactions that yields max profit.
 */
vector<transaction> BruteForceN2K(vector<transaction> T, vector<transaction> R, int index, int k)
{
    // Check if index is out of bounds, if that's the case then return current solution that has been built i.e R
    if(k == 0 || index > T.size()-1){
        return R;
    } 

    // Get the current transaction
    transaction current = T[index];
    
    // Check if current transaction is compatible with all the transactions that have been picked.
    bool isCompatible = true;   // Variable that keeps track of Compatability.
    for(auto r : R)
    {
        // if current stock does not have buy date greater than sell date of any transaction.
        // or if current stock does not have its sell date less than buy date of any transaction than declare them as incompatible.
        if( !((current.buy >= r.sell) || (current.sell <= r.buy)))  
        {
            isCompatible = false;
            break;
        }
    }
    
    if(isCompatible)
    {
        // If the transaction is indeed compatible then we have two choices
        // We either pick it 
        vector<transaction> R1 = R;
        R1.push_back(current);
        
        vector<transaction> T1 = BruteForceN2K(T, R1, index+1, k-1);
        int T1profit = totalProfit(T1);

        // Or we don't
        vector<transaction> T2 = BruteForceN2K(T, R, index+1, k);
        int T2profit = totalProfit(T2);

        // And return the Solution that has most profit amongst them
        if(T1profit > T2profit)
        {  
            return T1;
        }
        else
        {
            return T2;
        }

    }
    else
    {
        // Otherwise we have no choice but to proceed with next call.
        return BruteForceN2K(T, R, index+1, k);
    }
}

/**
 *   Task 4 of the programming project. Its time complexity is in order of m*n^2k.
 *   Computes and return at most k transactions that are maximum for given stocks m and given days n.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @param  k int                 - Max possible transactions
 *   @return   vector<transaction> - A vector of at most k transactions that yields max profit out of given transactions
 */
vector<transaction> Task4(vector<vector<int>> A, int m, int n, int k)
{
    // First compute all possible transactions
    vector<transaction> transactions;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int l = j + 1; l < n; l++)
            {
                int currentProfit = A[i][l] - A[i][j];
                transactions.push_back(transaction {i, currentProfit, j, l});                    
            }
        }
    }

    // Now pick atmost k transactions with max profit
    // i.e. try all (n^2)Ck pairs
    vector<transaction> R;
    vector<transaction> result = BruteForceN2K(transactions, R, 0, k);

    // Sorting transactions in order of their buy date
    sort(result.begin(), result.end(), compare);

    return result;
}

// Main Method
int main() 
{
    /**
     *  Get the inputs `k`, `m`, `n` & `A` which are specified as below:
     *  k    - Line 1 consists of one integer k.
     *  m, n - Line 2 consists of two integers m & n separated by one space character.
     *  A    - Next m lines each contains of n integers (prices for n days) separated by a single space.
     */
    int m, n, k;
    cin >> k >> m >> n;

    vector<vector<int>> A(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }

    // Get the result of task 4
    vector<transaction> result = Task4(A, m, n, k);

    // Print the result.
    for(auto r : result)
    {
        cout<<r.stock<<" "<<r.buy<<" "<<r.sell<<endl;
    }

    return 0;
}