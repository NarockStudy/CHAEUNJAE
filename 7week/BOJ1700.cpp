// 백준 문제 : 멀티탭 스케줄링 (미완)

#include <iostream>
#include <set>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N,K;
    cin >> N >> K;

    int step[K];
    for(int i=0;i<K;i++){
        cin >> step[i];
    }

    // 반복할때 i=i+N 하면서 반복
    // i ~ i+N에 기존 set의 원소가 있다면 해당 원소 삭제 X 처리하고 넘어감
    // set에 없는 원소라면 삭제 O 처리한 원소중에 하나 삭제하고 insert + ans++ 까지
    int ans = 0;
    set<int> multitab;
    vector<bool> isOkayErase;
    for(int i=0;i<K;i=i+N){
        for(int j=i;j<i+N;j++){
            if(multitab.size() >= N){

            }
            multitab.insert(step[j]);
        }
    }
    
}

