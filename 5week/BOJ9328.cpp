// 백준 문제 : 열쇠 (visited 제거 버전)

#include <iostream>
#include <vector>
#include <queue>
#include <cctype>

using namespace std;

int dy[4] = {-1, 0, 1, 0}; // 상, 우, 하, 좌 순서
int dx[4] = {0, 1, 0, -1};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for(int i=0;i<T;i++){
        int h,w;
        cin >> h >> w;

        queue<pair<int,int>> qp;
        vector<pair<int,int>> doors[26];
        // bool visited[h][w];
        char board[h][w];
        int keys[26];
        fill(keys,keys+26,0);
        int ans = 0;
        for(int j=0;j<h;j++){
            string str;
            cin >> str;
            for(int z=0;z<w;z++){
                // 배열 초기화
                board[j][z] = str[z];
                // visited[j][z] = false;
                
                // 빌딩 모서리 탐색
                if(j == 0 || j == h-1 || z == 0 || z == w-1){ // 빌딩의 모서리 중 
                    if(board[j][z] == '.'){ // 빈 공간이 있으면 큐에 푸쉬
                        qp.push({j,z});
                        board[j][z] = '-'; // '-'는 방문한 칸을 의미
                        // visited[j][z] = true;
                    } else if(islower(board[j][z])){ // 열쇠가 있을 때
                        qp.push({j,z});
                        // visited[j][z] = true;
                        keys[board[j][z] - 'a'] = 1;
                        board[j][z] = '-';
                    } else if(board[j][z] == '$'){ // 문서가 있을 때
                        qp.push({j,z});
                        // visited[j][z] = true;
                        board[j][z] = '-';
                        ans++;
                    }
                }
            }
        }

        
        string keyStr;
        cin >> keyStr;
        if(keyStr != "0"){
            for(auto s:keyStr){
                keys[s-'a'] = 1;
            }
        } 
        

        for(int j=0;j<h;j++){
            for(int z=0;z<w;z++){
                if(j == 0 || j == h-1 || z == 0 || z == w-1) {
                    if(isupper(board[j][z])){ // 문일 때
                        if(keys[tolower(board[j][z])-'a'] == 1){ // 열쇠가 있다면 큐에 넣고 방문 처리
                            qp.push({j,z});
                            // visited[j][z] = true;
                            board[j][z] = '-';
                        } else {
                            doors[board[j][z]-'A'].push_back({j,z});
                        }
                    }
                } 
            }
        }
        
        while(!qp.empty()) {

            auto cur = qp.front(); qp.pop();
            // cout << cur.first << " " << cur.second << "\n";  
            for(int dir=0;dir<4;dir++){
                int nxtY = cur.first + dy[dir];
                int nxtX = cur.second + dx[dir];
                if(0 <= nxtY && nxtY < h && 0 <= nxtX && nxtX < w){
                    // 열쇠일 때
                    if(islower(board[nxtY][nxtX])){
                        qp.push({nxtY,nxtX});
                        // visited[nxtY][nxtX] = true;
                        keys[board[nxtY][nxtX]-'a'] = 1;

                        if(!doors[toupper(board[nxtY][nxtX])-'A'].empty()){ // 해당하는 문들을 다 열기
                            for(auto door:doors[toupper(board[nxtY][nxtX])-'A']){
                                // board 삭제
                                // queue 넣기
                                board[door.first][door.second] = '-';
                                qp.push({door.first,door.second});
                                // visited[door.first][door.second] = true;
                            }
                        }
                        board[nxtY][nxtX] = '-';
                    }

                    // 문일 때
                    else if(isupper(board[nxtY][nxtX])){
                        if(keys[tolower(board[nxtY][nxtX])-'a'] == 1){ // 열쇠가 있다면 큐에 넣고 방문 처리
                            qp.push({nxtY,nxtX});
                            // visited[nxtY][nxtX] = true;
                            board[nxtY][nxtX] = '-';
                        } else {
                            doors[tolower(board[nxtY][nxtX])-'a'].push_back({nxtY,nxtX});
                        }
                    }

                    // 문서일 때
                    else if(board[nxtY][nxtX] == '$'){
                        qp.push({nxtY,nxtX});
                        // visited[nxtY][nxtX] = true;
                        board[nxtY][nxtX] = '-';
                        ans++;
                    }

                    // 빈 곳일 때
                    else if(board[nxtY][nxtX] == '.'){
                        qp.push({nxtY,nxtX});
                        // visited[nxtY][nxtX] = true;
                        board[nxtY][nxtX] = '-';
                    }

                }
            }
        }
        
        cout << ans << "\n";
    }
}