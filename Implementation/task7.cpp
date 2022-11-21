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
    int profit = 0;
    for(auto t : T)
    {
        profit += t.profit;
    }
    return profit;
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
 *   BruteForce2n is the brute force algorithm for Task7. Its time complexity is in order of m*2^n.
 *   Computes and returns those transactions that yield max profit for given stocks m and given days n and given cooldown c.
 *   Here transactions are not returned in sorted order.
 * 
 *   @param  A          vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  current    int                 - index of current element
 *   @param  S          int                 - index of current stock that is bought
 *   @param  D          int                 - index of current day that was stock S bought on.
 *   @param  buy        bool                - Boolean falg that indicates can we buy or not
 *   @param  c          int                 - Cooldown
 *   @return            vector<transaction> - A vector of transactions that yields max profit
 */
vector<transaction> BruteForce2n(vector<vector<int>> A, int current, int S, int D, bool buy, int c)
{
    // if index is out of range we've reached the base element, we will initialize a empty vector to return it.
    // And then in super problems we will push transactions on this vector as we go.
    if(current >= A[0].size())
    {
        vector<transaction> T;
        return T;
    }

    if(buy)
    {
        // Here we can buy stock
        // What is the max profit if we don't buy a stock on current day?
        vector<transaction> T = BruteForce2n(A, current+1, -1, -1, buy, c);

        // What is the max profit if we do buy a stock on current day?
        vector<transaction> C;   
        for(int i = 0; i < A.size(); i++)
        {
            vector<transaction> T1 = BruteForce2n(A, current+1, i, current, false, c);
            if(totalProfit(C) < totalProfit(T1))
            {
                C = T1;
            }
        }

        // Return the max profit of the two
        if(totalProfit(C) > totalProfit(T)) return C;
        return T;
    }
    else
    {
        // Here a stock is already bought, so we have two choices either sell a stock or we don't
        // What is the max profit if we don't sell the bought stock on current day?
        vector<transaction> T = BruteForce2n(A, current+1, S, D, false, c);

        // What is the max profit if we do sell the bought stock on current day?
        vector<transaction> C = BruteForce2n(A, current+c+1, -1, -1, true, c);
        
        // A transaction has occured so we do need to add the said transaction to the result C
        C.push_back(transaction {S, A[S][current] - A[S][D], D, current});

        if(totalProfit(T) > totalProfit(C)) return T;
        return C;
    }
    
}

/**
 *   Task 7 of the programming project. Its time complexity is in order of m*2^n.
 *   Computes and returns those transactions that yield max profit for given stocks m and given days n and given cooldown c.
 *
 *   @param  A vector<vector<int>> - a `m x n` stock where A[i][j] = Price of stock `i` at `jth` day 
 *   @param  m int                 - Number of Stocks
 *   @param  n int                 - Number of Days
 *   @param  c int                 - Cooldown
 *   @return   vector<transaction> - A vector of transactions that yields max profit
 */
vector<transaction> Task7(vector<vector<int>> A, int m, int n, int c)
{
    // Call the recursive solution algorithm
    vector<transaction> result = BruteForce2n(A, 0, -1, -1, true, c);

    // Sort the transactions in order of their buy date.
    sort(result.begin(), result.end(), compare);

    // Return the result.
    return result;
}

// Main method
int main()
{
    /**
     *  Get the inputs `k`, `m`, `n` & `A` which are specified as below:
     *  k    - Line 1 consists of one integer k.
     *  m, n - Line 2 consists of two integers m & n separated by one space character.
     *  A    - Next m lines each contains of n integers (prices for n days) separated by a single space.
     */
    int m, n, c;
    cin >> c >> m >> n;

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
    // infile.open("../ComparisonTask/TestCasesPlot67/Task7/" + name + ".txt");
    // infile >> c >> m >> n;
    // cout<< "N : " << n << endl;
    // cout<< "M : " << m << endl;
    // cout<< "C : " << c << endl;
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
    // vector<transaction> transactions = Task7(A, m, n, c);
    // t = clock() - t;
    // cout<<(float)t/CLOCKS_PER_SEC<<" seconds"<<endl;

    // Get the result of Task7
    vector<transaction> transactions = Task7(A, m, n, c);

    // Print the result
    for(auto t : transactions)
    {
        cout<<t.stock<<" "<<t.buy<<" "<<t.sell<<endl;
    }
    return 0;
}