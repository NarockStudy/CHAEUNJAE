// 백준 문제 : Gaaaaaaaaaarden

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌 순서
int dx[4] = {0, 1, 0, -1};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N,M,G,R;
    cin >> N >> M >> G >> R;
    
    int board[N][M]; // (0: 호수, 1,2 : 땅, 3 : 초록 배양액, 4: 빨간 배양액, 5: 꽃)
    vector<pair<int,int>> locations; // 배양액을 뿌릴 수 있는 땅의 인덱스 {y,x}
    vector<int> mask {2, 1, 1, 3, 2, 3, 2, 1, 1, 3}; // (1: 배양액 없음, 2: 초록 배양액, 3: 빨강 배양액)
    int gCnt = 0;
    int rCnt = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin >> board[i][j];
            
            // 조합을 생성할 mask 집합에 원소 넣기
            if(board[i][j] == 2){
                locations.push_back({i,j});
                // if(gCnt < G){
                //     mask.push_back(2);
                //     gCnt++;
                // } else if(rCnt < R){
                //     mask.push_back(3);
                //     rCnt++;
                // } else {
                //     mask.push_back(1);
                // }
            }
        }
    }
    // for(auto l:locations){
    //     cout << l.first << "," << l.second << "\n";
    // }

    int ans = 0;
    // do {
        for(int i=0;i<mask.size();i++){
            cout << mask[i] << " ";
        }
        cout << "\n";
        // board를 각 조합마다 사용할 realBoard에 복사
        int realBoard[N][M];
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                realBoard[i][j] = board[i][j];
            }
        }

        int flowerCnt = 0;
        queue<tuple<int,int,int>> qt; // {y, x, 색(2 : 초록, 3: 빨강)}
        for(int i=0;i<mask.size();i++){
            if(mask[i] == 2) {
                qt.push(make_tuple(locations[i].first,locations[i].second,2));
                realBoard[locations[i].first][locations[i].second] = 3;
            } else if(mask[i] == 3) {
                qt.push(make_tuple(locations[i].first,locations[i].second,3));
                realBoard[locations[i].first][locations[i].second] = 4;
            }
        }

        cout << "=================\n";
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                cout << realBoard[i][j] << " ";
            }
            cout << "\n";
        }

        int isBlooming[N][M]; // (-1 : 개화 불가, 0 : 방문 안함, 1: 초록 배양액만 있음, 2: 빨강 배양액만 있음, 3: 꽃)
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(realBoard[i][j] == 1 || realBoard[i][j] == 2) isBlooming[i][j] = 0;
                else isBlooming[i][j] = -1;
            }
        }

        while(true){
            queue<tuple<int,int,int>> qt2;

            while(!qt.empty()){
                auto cur = qt.front(); qt.pop();
                if(realBoard[get<0>(cur)][get<1>(cur)] == 5) continue;
                cout << "qt 1회전" << get<0>(cur) << " " << get<1>(cur) << " " << get<2>(cur) << "\n";

                for(int i=0;i<4;i++){
                    int nxtY = get<0>(cur) + dy[i];
                    int nxtX = get<1>(cur) + dx[i];
                    int nxtColor = get<2>(cur);
                    if(0 <= nxtY && nxtY < N && 0 <= nxtX && nxtX < M){
                        if(realBoard[nxtY][nxtX] == 1 || realBoard[nxtY][nxtX] == 2){
                            
                            if(nxtColor == 2){
                                if(isBlooming[nxtY][nxtX] == 0){ 
                                    isBlooming[nxtY][nxtX] = 1;
                                    qt2.push(make_tuple(nxtY,nxtX,2)); /////////
                                } else if(isBlooming[nxtY][nxtX] == 2){
                                    isBlooming[nxtY][nxtX] = 3;
                                    flowerCnt++;
                                }
                            } else if(nxtColor == 3){
                                if(isBlooming[nxtY][nxtX] == 0){ 
                                    isBlooming[nxtY][nxtX] = 2;
                                    qt2.push(make_tuple(nxtY,nxtX,3));
                                } else if(isBlooming[nxtY][nxtX] == 1){
                                    isBlooming[nxtY][nxtX] = 3;
                                    flowerCnt++;
                                }
                            }
                            cout << "isBlooming : \n";
                            for(int j=0;j<N;j++){
                                for(int z=0;z<M;z++){
                                    cout << isBlooming[j][z] << " ";
                                }
                                cout << "\n";
                            }
                        }
                    }
                }     
            }
            qt = qt2;
            
            
            // 다음 턴 대비 realBoard에 배양액, 꽃 실제로 채우기 + isBlooming 초기화
            cout << "realBoard : \n";
            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    if(isBlooming[i][j] == 0 || isBlooming[i][j] == -1){
                        
                    } else {
                        realBoard[i][j] = isBlooming[i][j] + 2; 
                        // if(realBoard[i][j] == 5) flowerCnt++;
                    }
                    cout << realBoard[i][j] << " ";
                    if(realBoard[i][j] == 1 || realBoard[i][j] == 2) isBlooming[i][j] = 0;
                    else isBlooming[i][j] = -1;
                }
                cout << "\n";
            }


            // if qt.empty면 break;
            if(qt.empty()){
                break;
            }
        }
        // cout << "flowerCnt : " << flowerCnt << "\n";
        ans = max(ans,flowerCnt);
        // if(flowerCnt == 8){
        //     for(int i=0;i<mask.size();i++){
        //         cout << mask[i] << " ";
        //     }
        //     cout << "\n";
        //     for(int i=0;i<N;i++){
        //         for(int j=0;j<M;j++){
        //             cout << realBoard[i][j] << " ";
        //         }
        //         cout << "\n";
        //     }
        // }
    // } while(next_permutation(mask.begin(),mask.end()));

    cout << ans << "\n";
}