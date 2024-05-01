#include <iostream>
#include <algorithm>
#define MAX_n 100000
using namespace std;

int n, m;
int arr[MAX_n];

int lowerbound(int target) { // target보다 같거나 큰 최초의 위치
    int left = 0, right = n-1;
    int min_idx = n;
    while (left <= right) {
        int mid = (left+right)/2;
        if(arr[mid] >= target) {
            right = mid-1;
            min_idx = min(min_idx, mid);
        }
        else{
            left = mid+1;
        }
    }

    return min_idx;
}

void input(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }    
}

void pro(){
    while(m--){
        int num;
        cin >> num;

        int pos = lowerbound(num);
        if(pos<n && arr[pos]==num){
            cout << pos+1 << "\n"; // 배열이라서 0부터 시작했지만 실제 위치는 1부터 시작으로 치니까
        }
        else{
            cout << "-1\n";
        }
    }
}

int main() {
    input();
    pro();       
}