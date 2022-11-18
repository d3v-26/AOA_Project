#include <bits/stdc++.h>

using namespace std;



int opt(vector<vector<int>> &A,  vector<vector<int>> &DP, vector<vector<int>> &buy, vector<vector<int>> &MaxProfit , int M, int N, int C)
{
    for(int j=1; j<N; j++)
    {
        for(int i=0; i<M;i ++)
        {

                int NewProfit = DP[M-1][max(0,j-C-2)] - A[i][j-1]  ;  
                if(NewProfit >= MaxProfit[i][0])
                {
                     MaxProfit[i][0]=NewProfit;
                     MaxProfit[i][1]=j-1;
                }
                
               
                if(i==0)
                {
                    int temp=DP[i][j];
                    DP[i][j]=max (  max(DP[i][j],DP[i][j-1]) , A[i][j] + MaxProfit[i][0] );
                    if(temp!=DP[i][j]){
                        buy[i][j]= MaxProfit[i][1];
                    }
                }
                else{
                    int temp=DP[i][j];
                    DP[i][j]=max ( max ( max(DP[i][j],DP[i][j-1]), DP[i-1][j] ) , A[i][j] + MaxProfit[i][0] );
                    if(temp!=DP[i][j]){
                        buy[i][j]= MaxProfit[i][1];
                    }
                }
        }
    }

    int i=M-1,j=N-1;
    while(j > 0)
    {
        if(i==0 && DP[i][j]==DP[i][j-1])
        {
            j-=1;
            
        }
    
        else if(i>0 && DP[i][j]==DP[i-1][j])
        {
            i=i-1;
        }
        else if(DP[i][j]==DP[i][j-1])
        {
            j=j-1;
        }
        else{
            cout<<i<<" "<<buy[i][j]<<" "<<j<<" "<<endl;
            
            j=buy[i][j]-C-1;
            i=M-1;
        }
        
    }
   
}


int main()
{
    int c, n, m; 
    cin>>c;
    cin>> m >> n;
    
    vector<vector<int>> A(m, vector<int> (n, 0));
    vector<vector<int>> DP(m, vector<int> (n, 0));
    vector<vector<int>> Buy(m, vector<int> (n, 0));
    vector<vector<int>> MaxProfit(m, vector<int> (2, 0));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> A[i][j];
        }
    }
    
    opt(A,DP,Buy,MaxProfit,m,n,c);
    
    
}




