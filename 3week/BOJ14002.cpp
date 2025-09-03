// 백준 문제 : 가장 긴 증가하는 부분 수열 4

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    int A[N]; // 원본 배열
    int S[N]; // 인덱스 i까지의 최대 증가 부분 수열 원소 수
    int beforeE[N]; // 인덱스 i까지의 최대 증가 부분 수열의 이전 원소 인덱스 배열, 역추적을 위해서 필요

    for(int i=0;i<N;i++){
        cin >> A[i];
        S[i] = 1;
        beforeE[i] = i;
    }

    int ans = S[0];
    int ansIndex = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            // i로 각 원소 반복
            // j로 i보다 작을 동안 이전 원소 반복
            if(A[j] < A[i]) { // 두 요소가 증가하는 관계에 있을 때

                // 대소 비교해서 개수 배열에 저장 
                S[i] = max(S[i],S[j]+1); 
                if(S[i] == S[j]+1){ // 값이 변했다면 이전 원소 인덱스 기록
                    beforeE[i] = j;
                }

                if(ans < S[i]) {
                    ans = S[i];
                    ansIndex = i;
                }
            }
        }
    }

    cout << ans << "\n";
    
    // 최대 증가 부분 수열 원소 역추적
    int curIndex = ansIndex;
    vector<int> revArr;
    revArr.push_back(A[curIndex]);
    while(beforeE[curIndex] != curIndex){
        curIndex = beforeE[curIndex];
        revArr.push_back(A[curIndex]);
    }
    reverse(revArr.begin(),revArr.end());
    for(auto a:revArr){
        cout << a << " ";
    }
    cout << "\n";

}