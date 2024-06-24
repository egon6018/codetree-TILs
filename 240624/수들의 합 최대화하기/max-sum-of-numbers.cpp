#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_n 10
using namespace std;

int n;
int board[MAX_n][MAX_n];
bool visited[MAX_n];
vector<int> picked;
int ans = 0;

void input() {
    cin >> n;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> board[i][j];
        }
    }
}

void findMax(int row) { // row: 현재 색칠된 칸을 선택할 행
    if(row == n){
        int sum = 0;
        for(int i=0;i<(int)picked.size();i++){
            sum += board[i][picked[i]];
        }

        ans = max(ans, sum); // 최댓값으로 update
        return;
    }

    for(int i=0;i<n;i++){ // 현재행에서 색칠할 열
        if(visited[i]){
            continue;            
        }

        visited[i] = true;
        picked.push_back(i);

        findMax(row+1);

        visited[i] = false;
        picked.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    findMax(0);
    cout << ans;

    return 0;
}