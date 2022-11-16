#include <bits/stdc++.h>

using namespace std;

vector <int> MaxProfit;

int opt(vector<vector<int>> &A, int M, int N, int C,int buy)
{
    int optA,optB;
    if(A[0].size()<=N){
        return 0;
    }
    if(buy==-1){
       optA = opt(A,M,N+1,C,buy);                // no transcation
       optB = opt(A,M,N+1,C,N) - A[M][N];        // buying stock M at i(th) day
       
    }
    else{
       
       optA = opt(A,M,N+1,C,buy);                //no transcation
       optB = opt(A,M,N+C+1,C,-1) + A[M][N];     //selling stock M at i(th) day
       if(buy>0)
       {
           MaxProfit[N]=max(MaxProfit[N],(A[M][N]-A[M][buy] + MaxProfit[min(max(0,N-C-1),max(0,buy-C-1))]));
       }
       else if(buy==0)
       {
            MaxProfit[N]=max(MaxProfit[N],(A[M][N]-A[M][buy] + 0));
       }
    }
    
    return max(optA,optB);
}


int main()
{
    int c, n, m;
    cin >>c>> m >> n;
    
    vector<vector<int>> A(m, vector<int> (n, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        MaxProfit.push_back(0);
    }
    for(int i=0;i<m;i++)
    {
        opt(A, i, 0, c,-1);
    }
    for(int i=0;i<m;i++)    
    {
        opt(A, i, 0, c,-1);
    }
    int maximum=0;
    for(int i=0;i<n;i++)
    {
        maximum=max(maximum,MaxProfit[i]);
        
    }
    cout<<maximum<<endl;
}
