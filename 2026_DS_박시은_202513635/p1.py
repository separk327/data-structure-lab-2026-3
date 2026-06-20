A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    answer = []
    queue = [0]
    visited = set([0])

    while queue:
        current = queue.pop(0)
        answer.append(current)

        for neighbor in sorted(A[current]):
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)

    return answer


def dfs(A):
    answer = []
    stack = [0]
    visited = set([0])

    while stack:
        current = stack.pop()
        answer.append(current)

        for neighbor in sorted(A[current], reverse=True):
            if neighbor not in visited:
                visited.add(neighbor)
                stack.append(neighbor)


    return answer

# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')