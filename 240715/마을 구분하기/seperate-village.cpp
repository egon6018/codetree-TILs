#include <iostream>
#include <queue>
#define MAX_n 25
using namespace std;

int n;
int town[MAX_n][MAX_n];
bool visited[MAX_n][MAX_n];
int town_cnt; // 마을 개수
priority_queue<int> people_cnt; // 각 마을에 내 사람의 수
int dr[4]={0,1,0,-1}; // 동,남,서,북
int dc[4]={1,0,-1,0}; // 동,남,서,북
bool inRange(int curr_r, int curr_c){
    return (curr_r>=0) && (curr_r<n) && (curr_c>=0) && (curr_c<n);
}

void input(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> town[i][j]; // 사람이 있으면 1, 벽이 있으면 0
        }
    }
}

void dfs(int curr_r, int curr_c){
    for(int i=0;i<4;i++){
        int next_r = curr_r + dr[i];
        int next_c = curr_c + dc[i];

        if(!inRange(next_r, next_c)){
            continue;
        }

        if(!visited[next_r][next_c] && town[next_r][next_c]){
            visited[next_r][next_c] = true;
            town_cnt++;
            dfs(next_r, next_c);
        }
    }
}

void pro(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){            
            if(town[i][j] && !visited[i][j]){
                town_cnt = 0; // 다른 마을일테니까 리셋
                visited[i][j] = true;
                town_cnt = 1;     
                dfs(i,j);       
                people_cnt.push(-town_cnt); // 각 마을에 몇명이었는지 오름차순으로    
            }                         
        }
    }

    cout << town_cnt << "\n";
    while(!people_cnt.empty()){
        cout << -people_cnt.top() << "\n";
        people_cnt.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    pro();

    return 0;
}