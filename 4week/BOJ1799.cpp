// 백준 문제 : 비숍 (3% 시간초과)

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

    vector<pair<int,int>> locations;
    vector<int> mask; // (0: 비숍 배치 안 한곳, 1: 비숍 배치 한 곳) 
    int board[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> board[i][j];
            if(board[i][j] == 1){
                locations.push_back({i,j});
                mask.push_back(0); // 우선 비숍 배치 안 한 곳으로 초기화
            } 
        }
    }

    bool isFail = false;
    int ans = 0;
    while(isFail == false){ // 어떤 수로도 해당 수의 비숍을 놓을 수 없을 때 반복 종료
        isFail = true;
        fill(mask.begin(),mask.begin()+ans,1);
        fill(mask.begin()+ans,mask.end(),0);
        sort(mask.begin(),mask.end());
        // cout << "ans : " << ans << "\n";
        
        do {
            // cout << "==================\n";
            // for(auto m:mask){
            //     cout << m << " ";
            // }
            // cout << "\n";


            vector<vector<int>> realBoard(N,vector<int>(N,0)); // (0: 비숍 배치 안 한곳, 1: 비숍 배치 한 곳) 
            queue<pair<int,int>> qp;
            bool isSubFail = false;
            for(int i=0;i<mask.size();i++){
                if(mask[i] == 1){
                    realBoard[locations[i].first][locations[i].second] = 1;
                    qp.push({locations[i].first,locations[i].second});
                }
            }

            // for(int i=0;i<N;i++){
            //     for(int j=0;j<N;j++){
            //         cout << realBoard[i][j] << " ";
            //     }
            //     cout << "\n";
            // }

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
                // cout << "isSubFail false\n";
                isFail = false;
                ans++;
                break;
            } else {
                // cout << "isSubFail true\n";
            }

        } while(next_permutation(mask.begin(), mask.end()));
    }
    
    cout << ans-1 << "\n";
}