// 백준 문제 : 소문난 칠공주

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

char board[5][5];
int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌 순서
int dx[4] = {0, -1, 0, 1};
int answer = 0;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			cin >> board[i][j];
		}
	}

	vector<bool> mask(25,false); // 조합을 저장하는 배열, 조합에 해당하는 원소는 false, 인덱스를 2차원 배열을 일렬로 나열한 인덱스를 사용
	fill(mask.begin()+7,mask.end(),true);
	
	do{
		// 벡터에 해당 정점 넣기
		// 처음 만난 조합의 정점을 큐에 넣고 bfs
		// bfs가 끝나고 count가 7이라면 && sCount가 4 이상이라면 answer++
		int count = 0;
		int sCount = 0;
		
        // 벡터에 해당 정점 넣기
		// 처음 만난 조합의 정점을 큐에 넣기
		vector<vector<bool>> isSelected(5,vector<bool>(5,false)); // 조합에 해당하는 인덱스의 요소를 true로 기록
		queue<pair<int,int>> qp; // {y,x}
		vector<vector<bool>> visited(5,vector<bool>(5,false)); // 방문한 인덱스의 요소를 true로 기록
		bool isFirst = true;
		for(int i=0;i<25;i++){
			if(mask[i] == false){ 
				isSelected[i/5][i%5] = true;
				if(isFirst == true) { // 조합 중 맨처음 발견된 원소만 큐에 push
					qp.push({i/5,i%5});
					visited[i/5][i%5] = true;
					count++;
					if(board[i/5][i%5] == 'S') sCount++;
					isFirst = false;
				}					
			}
		}
		
        // bfs
		while(!qp.empty()){
			auto p = qp.front(); qp.pop();
			int curY = p.first;
			int curX = p.second;
			
			for(int i=0;i<4;i++){
				int nxtY = curY + dy[i];
				int nxtX = curX + dx[i];
				if(0 <= nxtY && nxtY < 5 && 0 <= nxtX  && nxtX < 5){
					if(visited[nxtY][nxtX] == false){
						if(isSelected[nxtY][nxtX] == true){
							qp.push({nxtY,nxtX});
							count++;
							if(board[nxtY][nxtX] == 'S') sCount++;
							visited[nxtY][nxtX] = true;
						}
					}
				}
			}
		}
		
        // 수행한 결과가 조건에 만족한다면 answer++
		if(count == 7){
			if(sCount >= 4){
				answer++;
			}
		}
	}while(next_permutation(mask.begin(),mask.end())); // 25개 중에 7개 조합 뽑으면서 반복

	cout << answer << "\n";
}