#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_n 10
#define INT_MAX 100000
using namespace std;

int n;
int cost[MAX_n+1][MAX_n+1];
bool visited[MAX_n+1];
vector<int> picked;
int ans = INT_MAX;

void input() {
    cin >> n;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> cost[i][j];
        }
    }

    // 1번지점 A11
    visited[1] = true; 
    picked.push_back(1);
}

void findMin(int cnt){ // cnt: 방문한 지점의 수
    if(cnt == n+1){
        int total_cost = 0;
        for(int i=0;i<(int)picked.size()-1;i++){
            int curr_cost = cost[picked[i]][picked[i+1]];

            if(curr_cost == 0){ // 만약 curr_cost==0이면 자기자신이라는 의미니까
                return;
            }

            total_cost += curr_cost;
        }

        // 최종적으로 1번지점으로 돌아왔을때
        int last_first_cost = cost[picked.back()][1];
        if(last_first_cost == 0) {
            return;
        }

        ans = min(ans, total_cost+last_first_cost); // 최소비용의 합으로 update
        return;        
    }   

    for(int i=1;i<=n;i++){
        if(visited[i]){
            continue;
        }

        visited[i] = true;
        picked.push_back(i);

        findMin(cnt+1);

        visited[i] = false;
        picked.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    findMin(2); // A12부터 시작
    cout << ans;

    return 0;
}