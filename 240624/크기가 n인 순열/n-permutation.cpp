#include <iostream>
#include <vector>
#define MAX_N 8
using namespace std;

int n;
bool visited[MAX_N+1];
vector<int> picked;

void getPermutation(int cnt) { // cnt: 지금까지 선택한 수가 몇개인지    
    if(cnt == n) { // 모두 선택했을때 출력하고 종료
        for(int i = 0; i < (int) picked.size(); i++) {
            cout << picked[i] << " ";
        }
        cout << "\n";
        return;
    }
    
    for(int i = 1; i <= n; i++) {
        if(visited[i]) {
            continue;
        }

        visited[i] = true;
        picked.push_back(i);

        getPermutation(cnt+1);

        visited[i] = false;
        picked.pop_back();
    }
}

void input() {
    cin >> n;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    getPermutation(0);

    return 0;
}