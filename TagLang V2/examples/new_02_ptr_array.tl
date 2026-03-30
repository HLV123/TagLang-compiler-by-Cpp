#   NEW 02 — @ptr + @array
#   Chu de: Quan ly bo nho dong va tinh kieu C/Go
#   Label: 8 (Go/C ptr) + 10 (C array)


@array {
    # Mang tinh kieu C
    int matrix[9]  = {1, 2, 3, 4, 5, 6, 7, 8, 9}
    int fib[8]     = {1, 1, 2, 3, 5, 8, 13, 21}
    int primes[6]  = {2, 3, 5, 7, 11, 13}

    char name1[]   = "Alice"
    char name2[]   = "Bob"
    char name3[]   = "Charlie"
    char *lang     = "TagLang"
    char *version  = "v2.0"

    # In mang
    print(matrix[0])
    print(matrix[4])
    print(matrix[8])
    print(fib[0])
    print(fib[5])
    print(primes[0])
    print(primes[5])
    print(name1)
    print(name2)
    print(name3)
    print(lang)
    print(version)
}

@ptr {
    # Thao tac con tro kieu Go/C
    var x int = 10
    var y int = 20
    var z int = 0
    var sum int = 0

    var px *int
    var py *int
    var pz *int
    var ps *int

    px = &x
    py = &y
    pz = &z
    ps = &sum

    # Thay doi gia tri qua con tro
    *px = 42
    *py = 58
    *pz = 100
    *ps = 999

    print(x)
    print(y)
    print(z)
    print(sum)
    print(*px)
    print(*py)

    # Ham nhan doi
    func double_it(ptr *int) {
        *ptr = 84
    }

    # Ham reset
    func reset(ptr *int) {
        *ptr = 0
    }

    # Ham nhan 3
    func triple(ptr *int) {
        *ptr = 126
    }

    double_it(&x)
    print(x)

    reset(&z)
    print(z)

    triple(&x)
    print(x)
}
