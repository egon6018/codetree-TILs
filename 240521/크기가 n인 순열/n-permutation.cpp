#include <iostream>
#include <vector>
 
#define MAX_N 8

using namespace std;

// 변수 선언
int n;
bool visited[MAX_N + 1];
vector<int> picked;

// 지금까지 선택한 수의 개수를 cnt라 했을 때
// 계속 탐색을 이어서 진행합니다.
void GetPermutation(int cnt) {
    // 모든 원소를 선택했을 때, 해당 순열을 출력합니다.
    if(cnt == n) {
        for(int i = 0; i < (int) picked.size(); i++)
            cout << picked[i] << " ";
        cout << endl;
        return;
    }

    // 앞에서부터 하나씩 원소를 선택합니다.
    for(int i = 1; i <= n; i++) {
        if(visited[i]) continue;
        visited[i] = true;
        picked.push_back(i);

        GetPermutation(cnt + 1);

        visited[i] = false;
        picked.pop_back();
    }
}

int main() {
    // 입력:
    cin >> n;

    GetPermutation(0);
    return 0;
}