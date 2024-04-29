#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
#define MAX_n 100
#define NOT_EXISTS make_pair(-1,-1)
using namespace std;

int n,k; // nxn, k번 반복, 인접한 칸들 중 x보다 작은 곳으로 전부 이동
queue<pair<int,int>> q;
pair<int,int> current; // 현재위
int board[MAX_n+1][MAX_n+1];
bool visited[MAX_n+1][MAX_n+1];
int dr[4]={0,1,0,-1}; // 동,남,서,북
int dc[4]={1,0,-1,0}; // 동,남,서,북

bool inRange(int cur_r, int cur_c){
    return (cur_r>0) && (cur_r<=n) && (cur_c>0) && (cur_c<=n);
}

void initial(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            visited[i][j] = false;
        }
    }
}

bool go(int cur_r, int cur_c, int target){
    return inRange(cur_r, cur_c) && !visited[cur_r][cur_c] && (board[cur_r][cur_c] < target);
}

void BFS(){
    int cur_r, cur_c;
    tie(cur_r, cur_c) = current;
    visited[cur_r][cur_c] = true;
    q.push({cur_r, cur_c});

    int target = board[cur_r][cur_c];

    while(!q.empty()){
        tie(cur_r, cur_c) = q.front();
        q.pop();

        for(int i=0;i<4;i++){
            int next_r = cur_r + dr[i];
            int next_c = cur_c + dc[i];

            if(go(next_r, next_c, target)){
                q.push({next_r, next_c});
                visited[next_r][next_c] = true;
            }
        }
    }
}

bool update(pair<int, int> best_pos, pair<int, int> new_pos) {
    // 첫 도달 가능한 위치라면
    // update가 필요합니다.
    if(best_pos == NOT_EXISTS)
        return true;
    
    int best_x, best_y;
    tie(best_x, best_y) = best_pos;
    
    int new_x, new_y;
    tie(new_x, new_y) = new_pos;
    
    // 숫자, -행, -열 순으로 더 큰 곳이 골라져야 합니다.
    return make_tuple(board[new_x][new_y], -new_x, -new_y) >
           make_tuple(board[best_x][best_y], -best_x, -best_y);
}

bool Move(){
    initial();

    BFS();

    pair<int,int> best_pos = NOT_EXISTS;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!visited[i][j] || make_pair(i,j) == current){
                continue;
            }

            pair<int,int> new_pos = make_pair(i,j);
            if(update(best_pos, new_pos)){
                best_pos = new_pos;
            }
        }
    }

    if(best_pos == NOT_EXISTS){
        return false;
    }
    else{
        current = best_pos;
        return true;
    }
}

void input(){
    cin >> n >> k;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> board[i][j];
        }
    }

    int r,c;
    cin >> r >> c; // 시작위치
    current = make_pair(r,c); // 현재위치
}

void pro(){
    while(k--){

        if(!Move()){ // 움직이지 못하면 바로 종료
            break;
        }
    }

    int result_r, result_c;
    tie(result_r, result_c) = current;
    cout << result_r << " " << result_c;
}


int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}