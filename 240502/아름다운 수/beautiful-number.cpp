#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> sequence;
int answer=0;

void input(){
    cin >> n;
}

bool is_beautiful(){
    for(int i=0;i<n;i+=sequence[i]){ // 2이면 연속해서 2번, 3이면 연속해서 3번 나와야 하니까
        if((i+sequence[i]-1) >= n){ // 범위를 넘어가면
            return false;
        }

        for(int j=i;j<i+sequence[i];j++){
            if(sequence[j] != sequence[i]){
                return false;
            }
        }
    }
    return true;
}

void count_beautiful(int cnt){
    if(cnt == n){
        if(is_beautiful()){
            answer++;
        }
        return;
    }

    for(int i=1;i<=4;i++){
        sequence.push_back(i);
        count_beautiful(cnt+1);
        sequence.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    input();
    count_beautiful(0);
    cout << answer;

    return 0;
}