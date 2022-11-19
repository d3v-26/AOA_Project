#include <bits/stdc++.h>

using namespace std;

bool sortbysec(const tuple<int, int, int>& a, 
              const tuple<int, int, int>& b)
{
    return (get<1>(a) < get<1>(b));
}

void print( vector<tuple<int, int, int>>  OPT)
{
    sort(OPT.begin(), OPT.end(), sortbysec);
    for(int i = 0; i < OPT.size(); i++)
    {
       
        cout<< get<0>(OPT[i]) << " " <<get<1>(OPT[i]) << " " << get<2>(OPT[i]) << endl;
        
    }
    
}

int opt(vector<vector<int>> &A, vector<vector<int>> MaxProfit , int M, int N, int C, vector<vector<int>> &DP)
{
    int m=A.size();
    int n=A[0].size();
    
    if(N<=0){
        DP[M][N]=0;
        return 0;
    }
  
    if(M==0)
    {
        int ValueA=opt(A,MaxProfit,M ,N-1,C, DP);
        int ValueC=opt(A,MaxProfit,m-1 ,max(0,N-C-2),C, DP);
        int NewProfit = ValueC - A[M][N-1]; 
        if( NewProfit >= MaxProfit[M][0])
        {
             MaxProfit[M][0]=NewProfit;
             MaxProfit[M][1]=N-1;
        }
        DP[M][N]=max ( ValueA , A[M][N] + MaxProfit[M][0] );
        return DP[M][N];
    }
    
    int ValueA=opt(A,MaxProfit,M ,N-1,C, DP);
    int ValueB=opt(A,MaxProfit,M-1 ,N,C, DP);
    int ValueC=opt(A,MaxProfit,m-1 ,max(0,N-C-2),C, DP);
    int NewProfit = ValueC - A[M][N-1]; 
    
    if( NewProfit >= MaxProfit[M][0])
    {
         MaxProfit[M][0]=NewProfit;
         MaxProfit[M][1]=N-1;
    }
    DP[M][N]=max ( max(ValueA , ValueB) , A[M][N] + MaxProfit[M][0] );
    
    return DP[M][N];
    
}


int main()
{
    int c, n, m; 
    cin>>c;
    cin>> m >> n;
    
    vector<vector<int>> A(m, vector<int> (n, 0));
    vector<vector<int>> DP(m, vector<int> (n, 0));
    vector<vector<int>> MaxProfit(m, vector<int> (2, INT_MIN));
   // vector<tuple<int, int, int>> result;
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }
    
    cout<<opt(A,MaxProfit,m-1,n-1,c, DP)<<endl;
    
    // vector<tuple<int, int, int>> result;

    // int i=m-1,j=n-1;
    // while(j > 0)
    // {
    //     if(i==0 && DP[i][j]==DP[i][j-1])
    //     {
    //         j-=1;
    //     }
    //     else if(i>0 && DP[i][j]==DP[i-1][j])
    //     {
    //         i=i-1;
    //     }
    //     else if(DP[i][j]==DP[i][j-1])
    //     {
    //         j=j-1;
    //     }
    //     else{
    //         result.emplace_back(i, MaxProfit[i][1], j);
    //         j=MaxProfit[i][1]-c-1;
    //         i=m-1;
    //     }
    // }
    // print(result);
    
}






