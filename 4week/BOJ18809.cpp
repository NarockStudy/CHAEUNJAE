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
    
    int board[N][M]; // (0: 호수, 1,2 : 땅, 3: 초록 배양액, 4: 빨강 배양액, 5: 꽃)
    vector<pair<int,int>> locations; // 배양액을 뿌릴 수 있는 땅의 인덱스 {y,x}
    vector<int> mask; // (1: 배양액 없음, 2: 초록 배양액, 3: 빨강 배양액)
    int gCnt = 0;
    int rCnt = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin >> board[i][j];
            
            // 조합을 생성할 mask 집합에 원소 넣기
            if(board[i][j] == 2){
                locations.push_back({i,j});
                if(gCnt < G){
                    mask.push_back(2);
                    gCnt++;
                } else if(rCnt < R){
                    mask.push_back(3);
                    rCnt++;
                } else {
                    mask.push_back(1);
                }
            }
        }
    }
    sort(mask.begin(),mask.end()); // next_permutation 사용시에 정렬해줄 것.. 정렬 순서를 처음으로 돌려서 순열 반복이 정상적으로 이루어지게 해줌

    int ans = 0;
    do {
        // board를 각 조합마다 사용할 realBoard에 복사
        int realBoard[N][M];
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                realBoard[i][j] = board[i][j];
            }
        }

        int visitedGreen[N][M];
        int visitedRed[N][M];
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                visitedGreen[i][j] = -1;
                visitedRed[i][j] = -1;
            }
        }

        int flowerCnt = 0;
        queue<tuple<int,int,int,int>> qt; // {y, x, 색(2 : 초록, 3: 빨강), 시간}
        // 시간 기록으로 같은 시간에 온 배양액끼리만 개화되는 것을 구현 가능
        for(int i=0;i<mask.size();i++){
            if(mask[i] == 2) {
                qt.push(make_tuple(locations[i].first,locations[i].second,2,0));
                visitedGreen[locations[i].first][locations[i].second] = 0;
            } else if(mask[i] == 3) {
                qt.push(make_tuple(locations[i].first,locations[i].second,3,0));
                visitedRed[locations[i].first][locations[i].second] = 0;
            }
        }

        while(true){
            queue<tuple<int,int,int,int>> qt2; // 임시 queue

            while(!qt.empty()){
                auto cur = qt.front(); qt.pop();
                if(realBoard[get<0>(cur)][get<1>(cur)] == 5) continue; // 처음 배양액일때 push 됐다가 이후 꽃이 된 요소들 bfs 처리 제외

                for(int i=0;i<4;i++){
                    int nxtY = get<0>(cur) + dy[i];
                    int nxtX = get<1>(cur) + dx[i];
                    int nxtColor = get<2>(cur);
                    int nxtTime = get<3>(cur);
                    if(0 <= nxtY && nxtY < N && 0 <= nxtX && nxtX < M){
                        if(realBoard[nxtY][nxtX] == 1 || realBoard[nxtY][nxtX] == 2){ // 꽃, 호수가 아닌 땅일 때
                            if(nxtColor == 2){
                                if(visitedGreen[nxtY][nxtX] == -1){
                                    visitedGreen[nxtY][nxtX] = nxtTime+1;
                                    if(visitedRed[nxtY][nxtX] == nxtTime+1){
                                        realBoard[nxtY][nxtX] = 5; 
                                        flowerCnt++;
                                    } else {
                                        qt2.push(make_tuple(nxtY,nxtX,2,nxtTime+1));
                                    }
                                }
                            } else if(nxtColor == 3){
                                if(visitedRed[nxtY][nxtX] == -1){
                                    visitedRed[nxtY][nxtX] = nxtTime+1;
                                    if(visitedGreen[nxtY][nxtX] == nxtTime+1){
                                        realBoard[nxtY][nxtX] = 5; 
                                        flowerCnt++;
                                    } else {
                                        qt2.push(make_tuple(nxtY,nxtX,3,nxtTime+1));
                                    }
                                }
                            }
                        }
                    }
                }     
            }
            qt = qt2;

            if(qt.empty()){
                break;
            }
        }

        ans = max(ans,flowerCnt);

    } while(next_permutation(mask.begin(),mask.end()));

    cout << ans << "\n";
}

// --------------------------------------------------------------------

// 백준 문제 : Gaaaaaaaaaarden (mask 배열에 sort 안써서 5시간 날린; 시간 초과 버전)

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <tuple>

// using namespace std;

// int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌 순서
// int dx[4] = {0, 1, 0, -1};

// int main(){
//     cin.tie(0);
//     ios::sync_with_stdio(0);

//     int N,M,G,R;
//     cin >> N >> M >> G >> R;
    
//     int board[N][M]; // (0: 호수, 1,2 : 땅, 3 : 초록 배양액, 4: 빨간 배양액, 5: 꽃)
//     vector<pair<int,int>> locations; // 배양액을 뿌릴 수 있는 땅의 인덱스 {y,x}
//     vector<int> mask; // (1: 배양액 없음, 2: 초록 배양액, 3: 빨강 배양액)
//     int gCnt = 0;
//     int rCnt = 0;
//     for(int i=0;i<N;i++){
//         for(int j=0;j<M;j++){
//             cin >> board[i][j];
            
//             // 조합을 생성할 mask 집합에 원소 넣기
//             if(board[i][j] == 2){
//                 locations.push_back({i,j});
//                 if(gCnt < G){
//                     mask.push_back(2);
//                     gCnt++;
//                 } else if(rCnt < R){
//                     mask.push_back(3);
//                     rCnt++;
//                 } else {
//                     mask.push_back(1);
//                 }
//             }
//         }
//     }
//     sort(mask.begin(),mask.end());

//     int ans = 0;
//     do {
//         // board를 각 조합마다 사용할 realBoard에 복사
//         int realBoard[N][M];
//         for(int i=0;i<N;i++){
//             for(int j=0;j<M;j++){
//                 realBoard[i][j] = board[i][j];
//             }
//         }

//         int flowerCnt = 0;
//         queue<tuple<int,int,int>> qt; // {y, x, 색(2 : 초록, 3: 빨강)}
//         for(int i=0;i<mask.size();i++){
//             if(mask[i] == 2) {
//                 qt.push(make_tuple(locations[i].first,locations[i].second,2));
//                 realBoard[locations[i].first][locations[i].second] = 3;
//             } else if(mask[i] == 3) {
//                 qt.push(make_tuple(locations[i].first,locations[i].second,3));
//                 realBoard[locations[i].first][locations[i].second] = 4;
//             }
//         }

//         int isBlooming[N][M]; // (-1 : 개화 불가, 0 : 방문 안함, 1: 초록 배양액만 있음, 2: 빨강 배양액만 있음, 3: 꽃)
//         for(int i=0;i<N;i++){
//             for(int j=0;j<M;j++){
//                 if(realBoard[i][j] == 1 || realBoard[i][j] == 2) isBlooming[i][j] = 0;
//                 else isBlooming[i][j] = -1;
//             }
//         }

//         while(true){
//             queue<tuple<int,int,int>> qt2;

//             while(!qt.empty()){
//                 auto cur = qt.front(); qt.pop();
//                 if(realBoard[get<0>(cur)][get<1>(cur)] == 5) continue;

//                 for(int i=0;i<4;i++){
//                     int nxtY = get<0>(cur) + dy[i];
//                     int nxtX = get<1>(cur) + dx[i];
//                     int nxtColor = get<2>(cur);
//                     if(0 <= nxtY && nxtY < N && 0 <= nxtX && nxtX < M){
//                         if(realBoard[nxtY][nxtX] == 1 || realBoard[nxtY][nxtX] == 2){
                            
//                             if(nxtColor == 2){
//                                 if(isBlooming[nxtY][nxtX] == 0){ 
//                                     isBlooming[nxtY][nxtX] = 1;
//                                     qt2.push(make_tuple(nxtY,nxtX,2));
//                                 } else if(isBlooming[nxtY][nxtX] == 2){
//                                     isBlooming[nxtY][nxtX] = 3;
//                                     flowerCnt++;
//                                 }
//                             } else if(nxtColor == 3){
//                                 if(isBlooming[nxtY][nxtX] == 0){ 
//                                     isBlooming[nxtY][nxtX] = 2;
//                                     qt2.push(make_tuple(nxtY,nxtX,3));
//                                 } else if(isBlooming[nxtY][nxtX] == 1){
//                                     isBlooming[nxtY][nxtX] = 3;
//                                     flowerCnt++;
//                                 }
//                             }
//                         }
//                     }
//                 }     
//             }
//             qt = qt2;
            
//             // 다음 턴 대비 realBoard에 배양액, 꽃 실제로 채우기 + isBlooming 초기화
//             for(int i=0;i<N;i++){
//                 for(int j=0;j<M;j++){
//                     if(isBlooming[i][j] == 0 || isBlooming[i][j] == -1){
                        
//                     } else {
//                         realBoard[i][j] = isBlooming[i][j] + 2;
//                     }
//                     if(realBoard[i][j] == 1 || realBoard[i][j] == 2) isBlooming[i][j] = 0;
//                     else isBlooming[i][j] = -1;
//                 }
//             }

//             if(qt.empty()){
//                 break;
//             }
//         }
//         ans = max(ans,flowerCnt);
//     } while(next_permutation(mask.begin(),mask.end()));

//     cout << ans << "\n";
// }
