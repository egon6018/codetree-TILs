#include <iostream>
#define MAX_n 100
using namespace std;

int n,m,k; // n x n, m:블록의 크기(1 x m), k열~k+m-1열
int board[MAX_n][MAX_n];

void input(){
    cin >> n >> m >> k;
    k--; // board는 0열부터 주어진 k는 1열부터 의미하니까

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> board[i][j]; // 0:빈칸, 1:블럭채워져있음
        }
    }
}

bool isBlank(int row, int col_s, int col_e){ // col_s=k, col_e=k+m-1
    for(int col=col_s;col<=col_e;col++){
        if(board[row][col]){ // 해당 칸에 블럭이 있는가
            return false; // 블럭이 이미 존재한다면 빈칸 아님
        }
    }
    return true; // 해당 row에 해당col_s~col_e까지 모두 0이면 빈칸이라는 뜻
}

int getTargetRow(){
    for(int row=0;row<n-1;row++){
        if(!isBlank(row+1,k,k+m-1)){ // 다음 행에 블럭이 들어갈만큼의 열이 모두 비어있는지
            return row; // 막혀있다면 지금 row리턴
        }
    }
    return n-1; // 끝까지 확인했는데 모두 비어있었다면, 가장 아래행으로 내려감
}

void pro(){
    // 최종적으로 멈추게 될 행
    int row = getTargetRow();

    // 블럭이 들어갈 곳에 1 체크
    for(int col=k;col<=k+m-1;col++){
        board[row][col] = 1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}