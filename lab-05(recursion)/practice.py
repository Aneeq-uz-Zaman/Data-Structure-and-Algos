if __name__ == '__main__':
    n = int(input())
    arr = list(map(int, input().split()))  # convert map to list
    max_score = max(arr)                   # find the highest score
    runner_up = -9999999                   # just initial value

    for i in arr:
        if i != max_score and i > runner_up:
            runner_up = i

    print(runner_up)
