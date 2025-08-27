// 백준 문제 : 최솟값 찾기

#include <iostream>
#include <deque>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, L;
    cin >> N >> L;
    deque<int> dq; // A의 인덱스를 저장
    // front에서는 슬라이딩 윈도우의 인덱스를 넘는 것들을 잘라주고
    // back에서는 최소값 후보의 원소를 추가하며, 추가할 원소보다 A[i]가 큰 원소들(최소값 후보에서 탈락된 원소들)은 잘라줌
    // 그렇게해서 A[dq 인덱스]의 오름차순을 계속 유지 가능 

    int A[N];
    for(int i=0;i<N;i++){
        cin >> A[i];
    }
    dq.push_back(0);
    cout << A[0] << " ";

    for(int i=1;i<N;i++){

        // front 슬라이딩 윈도우 인덱스 검사 
        int bound = i-L+1>0 ? i-L+1 : 0;
        if(!dq.empty()){
            if(dq.front() < bound) dq.pop_front();
        }

        // 정답 출력
        if(dq.empty() || A[dq.front()] > A[i]) cout << A[i] << " ";
        else cout << A[dq.front()] << " "; 

        // back 최소값 후보 검사
        while(!dq.empty()){
            if(A[dq.back()] > A[i]) dq.pop_back();
            else break;
        }

        // back 새로운 최소값 후보 원소(i) 추가
        dq.push_back(i);
    }
    cout << "\n";
}