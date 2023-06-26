def main():
    a = int(input())
    b = input().split()
    c = input().split()
    b.remove(c[0])
    b.remove(c[1])
    b = [c[0]] + b + [c[1]]
    d = int(input())
    t = dict()
    count = 0
    for i in b:
        t[i] = count
        count += 1
    print(t)
    ans = []
    for i in range(d):
        e = list(input().replace('->', ' ').split())
        
        if e[4] == 'R':
            e[4] = '1'
        elif e[4] == 'L':
            e[4] = '0'
        else:
            e[4] = '2'

        ans.append(str(t[e[0]]) + ' ' + str(100 + ord(e[1]) - 33) + str(10 ** 5 + t[e[2]]) + str(100 + ord(e[3]) - 33) + e[4])
    f = input()
    print(a)
    print(*list(range(a)))
    print(0, a-1)
    print(d)
    for i in ans:
        print(i)
    print(f)


if __name__ == "__main__":
    main()