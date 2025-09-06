// 백준 문제 : 퇴사 2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    
    vector<pair<int,int>> arr; // 0 인덱스 시작
    for(int i=0;i<N;i++){
        int T,P;
        cin >> T >> P;
        arr.push_back({T,P});
    }

    int conSum[N+1]; // 각 인덱스일때 최대 누적합을 기록하는 배열
    fill(conSum,conSum+N+1,0);

    for(int i=0;i<N+1;i++){
        if(i > 0){
            conSum[i] = max(conSum[i], conSum[i-1]); // 이전 인덱스의 누적합을 현재 인덱스에서도 계속 이어서 가져오기 위해 필요
        }

        if(i + arr[i].first <= N){

            // 모든 인덱스를 선형 반복하면서
            // max([현재 일자 + 상담기간]의 누적합, [현재 일자]의 누적합 + [현재 일자]의 이익)
            // 로 누적합을 계속 쌓음
            // 그럼 누적합의 마지막 인덱스 요소가 정답이 됨 
            
            conSum[i+arr[i].first] = max(conSum[i + arr[i].first], conSum[i] + arr[i].second);
        }
     }
     cout << conSum[N] << "\n";

}