#include <iostream>
#include <vector>
#define MAX_N 8
using namespace std;

int n;
bool visited[MAX_N+1];
vector<int> picked;

void input(){
    cin >> n;
}
                                                                        
void getPermutation(int cnt){
    if(cnt == n){
        for(int i=0;i<(int)picked.size();i++){
            cout << picked[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i=1;i<=n;i++){
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

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    getPermutation(0);

    return 0;
}