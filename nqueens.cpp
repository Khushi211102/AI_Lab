#include<bits/stdc++.h>
using namespace std;

int cnt=0;
int n;

vector<vector<int>> board(101,vector<int>(101,0));


void show(){
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        cout<<board[i][j]<<" ";
                }
                cout<<endl;
        }
        cout<<"-------------------"<<endl;
}

bool isValid(int row, int col){

        //Check for horizontal positions
        for(int i=col;i>=0;i--){
                if(board[row][i]){
                        return false;
                }
        }
        int i=row,j=col;


        //check upper left diagonal
        while (i>=0 && j>=0)
        {
                if(board[i][j]){
                        return false;
                }
                i--;
                j--;
        }

        i=row;
        j=col;

        //check lower left diagonal
        while (i<8 && j>=0)
        {
                if(board[i][j]){
                        return false;
                }
                i++;
                j--;
        }
        return true;
        
        
}

void nQueens(int cur_col){
        if(cur_col >= n){
                return;
        }


        for(int i=0;i<n;i++){
                if(isValid(i,cur_col)){
                        board[i][cur_col]=1;

                        if(cur_col==n-1){
                                show();
                                cnt++;
                        }

                        nQueens(cur_col+1);
                        board[i][cur_col]=0;
                }
        }
}

void solve(){

        cin>>n;
        nQueens(0);
        cout<<cnt<<endl;
        return;

}

int main(){
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        int t;
        t=1;
        // cin >> t;
        // Hetu ka laptop
        
        while (t--) {
                solve();   
        }
        
        return 0;
}