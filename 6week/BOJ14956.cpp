// 백준 문제 : Philosopher’s Walk

#include <iostream>
#include <vector>

using namespace std;

#define X first
#define Y second

// 재귀 함수 (side : 한 변의 길이, walk : 걸음수)
pair<int,int> philo(int side, int walk){
    if(side == 2){
        switch(walk) {
            case 1:
                return {1, 1};
            case 2:
                return {1, 2};
            case 3:
                return {2, 2};
            case 4:
                return {2, 1};
        }
    }

    int half = side/2;
    int section = half * half; // 사분면 구분 걸음수의 첫번째 배수?, ex) side가 4일때 사분면을 구분하는 걸음수는 16, 32, 48, 64로 모두 16의 배수임

    if(walk <= section){
        // 3사분면

        pair<int,int> recur = philo(half,walk);
        // side가 2일때의 좌표에서 x,y가 뒤집힘
        return {recur.Y, recur.X};

    } else if(walk <= 2*section){
        // 2사분면
        pair<int,int> recur = philo(half,walk-section);
        return {recur.X, half + recur.Y};
    } else if(walk <= 3*section){
        // 1사분면
        pair<int,int> recur = philo(half, walk - 2 * section);
        return {half + recur.X, half + recur.Y};
    } else {
        // 4사분면
        pair<int,int> recur = philo(half, walk - 3 * section);
        // side가 2일때의 좌표에서 x,y가 뒤집힘
        return {2 * half - recur.Y + 1, half - recur.X + 1};
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    pair<int,int> ans = philo(n,m);
    cout << ans.X << " " << ans.Y << "\n";
}