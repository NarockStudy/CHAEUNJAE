// 백준 문제 : 비숍

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dy[4] = {-1, 1, 1, -1}; // 우상, 우하, 좌하, 좌상
int dx[4] = {1, 1, -1, -1};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;

    vector<pair<int,int>> mask; // {일렬 인덱스, (0: 비숍 배치 X, 1: 실제 비숍 배치)}
    int board[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> board[i][j];
            if(board[i][j] == 1) mask.push_back({i*N+j,0});
        }
    }

    // next_permutation 이란 {1, 2, 3}을 {3, 2, 1} 처럼 섞는것
    bool isFail = false;
    int ans = 1;
    while(isFail == false){
        for(int i=0;i<N*N;i++){
            mask[]
            for(int j=0;j<ans;j++){

            }
        }

        do {
            vector<vector<int>> realBoard(N,vector<int>(N,0));
            queue<pair<int,int>> qp;
            bool isSubFail = false;
            for(auto m:mask){
                if(m.second == 1){
                    realBoard[m.first/N][m.first%N] = 1;
                    qp.push({m.first/N,m.first%N});
                }
            }

            while(!qp.empty() && isSubFail == false){
                auto cur = qp.front(); qp.pop();
                
                for(int i=0;i<4;i++){
                    for(int j=1;j<N;j++){
                        int nxtY = cur.first + j * dy[i];
                        int nxtX = cur.second + j * dx[i];
                        if(0 <= nxtY && nxtY < N && 0 <= nxtX && nxtX < N){
                            if(realBoard[nxtY][nxtX] == 1){
                                isSubFail = true;
                                break;
                            }
                        } else {
                            break; // 보드를 벗어났으므로 현재 대각선 방향의 j 늘리기를 그만하고 i 늘리기
                        }
                    }
                    if(isSubFail == true) break;
                }
            }

            if(isSubFail == false){
                ans++;
                break;
            } else {

            }


        } while(next_permutation(mask.begin(), mask.end()));
    }
}