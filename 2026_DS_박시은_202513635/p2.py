import sys

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################

def count_stages(concerts):
    answer = 0

    if not concerts:
        return 0
    """
    case.txt가 주어지지 않거나 비어있는 경우, 무대가 0개 있다고 반환하여 에러가 나는 것을 방지한다.
    """

    N = len(concerts)
    """
    concerts라는 큰 리스트 안에 들어있는 요소들의 수를 세어 행의 개수를 구한다.
    """
    M = len(concerts[0])
    """
    concerts라는 큰 리스트 안의 첫 번째 리스트에 들어있는 요소들의 수를 세어 열의 개수를 구한다.
    """

    visited = [[False]*M for _ in range(N)]
    """
    무한루프에 빠지거나 중복으로 세는 것을 방지하기 위해 방문 여부를 확인하는 배열을 만들었다. 
    '[False]*M' 으로 방문하지 않은 상태의 행을 만들고 for _ in range(N)으로 이 행을 N번 생성하여 배열을 만드는데,
    '*N' 처럼 작성할 경우,N개의 행이 모두 같은 메모리 주소를 사용하여 얕은 복사 버그가 발생할 수 있으므로 'for _ in range(N)' 와 같이 작성했고,
    특정한 숫자를 쓰지 않고 단순히 생성 횟수만 반복할 것이기 때문에 'i' 같은 변수가 아닌 '_'를 사용하였다.
    """

    def is_valid_loc(r,c):
        if 0 <= r < N and 0 <= c < M:
            if concerts[r][c] == 0 and not visited[r][c]:
                return True
        return False
    """
    map을 탐색할 때 map의 범위를 벗어나 에러가 발생하는 것을 막고, 해당 위치가 유효한지 검사하는 함수 'is_valid_loc' 를 만들었다.
    'if 0 <= r < N and 0 <= c < M:' 를 통해 탐색하려는 위치가 배열 범위 안에 있는지 확인한다. 범위 안에 있다면
    'if concerts[r][c] == 0 and not visited[r][c]:' 를 통해 해당 위치가 빈공간이면서 아직 방문하지 않은 곳인지 확인한다. 
    두 조건을 만족할 때만 True를 반환하도록 하였다.   
    """

    def bfs(start_r, start_c):
        """
        이 문제는 미로찾기처럼 입구에서 출구까지 하나의 길을 찾는 것이 아니라, 콘서트장 약도에서 독립된 무대공간으로 쓸 수 있는 공간들의
        수를 파악하는 문제이다. 따라서 매번 마지막에 추가된 노드를 먼저 방문하는 dfs보다 먼저 저장된 노드부터 순차적으로 퍼져나가는 bfs가
        더 적합하다고 생각하여 bfs 방식을 선택하였다.
        """
        queue = []
        queue.append((start_r, start_c))
        visited[start_r][start_c] = True
        """
        방문 예정인 노드들을 저장할 queue 리스트를 만들고, 시작좌표를 리스트에 추가하여 탐색의 시작점을 정하였다.
        또한 시작점이 중복 삽입되어 무한 루프 오류가 일어나는 것을 방지하기 위해 시작점을 추가함과 동시에 
        'visited[start_r][start_c] = True' 를 통하여 방문처리 하였다.
        """

        while queue:
            r, c = queue.pop(0)
            """
            먼저 저장된 노드들부터 방문해야하므로 'queue.pop(0)' 를 통해 가장 먼저 저장된 좌표를 꺼내도록 하였다.
            """

            if is_valid_loc(r-1, c):
                queue.append((r - 1, c))
                visited[r-1][c] = True

            if is_valid_loc(r+1, c):
                queue.append((r + 1, c))
                visited[r+1][c] = True

            if is_valid_loc(r, c-1):
                queue.append((r, c - 1))
                visited[r][c-1] = True

            if is_valid_loc(r, c+1):
                queue.append((r, c + 1))
                visited[r][c+1] = True
            """
            시작점과 이어진 빈 공간의 범위를 파악하기 위한 코드이다.
            현재 위치를 기준으로 상(r-1, c), 하(r+1, c), 좌(r, c-1), 우(r, c+1)를 탐색하여 
            각 위치의 유효성을 검사한다. 'if is_valid_loc()' 를 통해 각 좌표가
            map의 범위 안에 있고 아직 방문하지 않았음을 확인하면, 'queue.append()' 를 통해 해당
            좌표를 방문 예정 리스트에 넣고, 동시에 'visited[][] = true' 를 통해 방문을 확인하여
            다른 경로에서 좌표가 중복 삽입되는 것을 방지하였다. 
            """

    for i in range(N):
        for j in range(M):
            if concerts[i][j] == 0 and not visited[i][j]:
                bfs(i, j)
                answer += 1

    return answer
    """
    독립된 무대공간이 몇 개 생기는지 계산하기 위한 코드이다. 
    map 범위 안에서 (0,0)부터 차례대로 탐색하다, 방문한 적 없는 빈공간(concerts[i][j] == 0 and not visited[i][j])을
    발견할때마다 해당 위치를 시작점으로 하는 bfs를 실행하여 시작점과 연결되는 무대공간을 모두 파악하면
    정답 카운트를 1 증가시키며, 'return answer' 를 통해 총 무대 개수를 반환한다. 
    """

print(count_stages(concerts))