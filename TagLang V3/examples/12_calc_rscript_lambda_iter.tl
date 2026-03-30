# ============================================================
#   FILE 12 — @calc + @rscript + @lambda + @iter
#   Chu de: Xu ly du lieu va thuat toan kieu functional
# ============================================================

@data {
    n:     10
    dem:   0
    tong:  0
}

@calc {
    pi       = 3.14159
    e        = 2.71828
    phi      = 1.61803
    sqrt2    = 1.41421
    n_sq     = n ^ 2
    n_cube   = n ^ 3
}

@rscript {
    # Hang so toan hoc R-style
    radius <- 7
    height <- 12

    # Cac phep tinh R-style
    area_circle  <- 3.14159
    vol_cylinder <- 3.14159

    nums <- c(3, 1, 4, 1, 5, 9, 2, 6, 5, 3)

    print(radius)
    print(height)
    print(nums)
}

@lambda {
    # C# style arrow functions
    square   = x => x * x
    cube     = x => x * x * x
    double_v = x => x * 2
    add      = (x, y) => x + y
    multiply = (x, y) => x * y
    average  = (x, y) => (x + y) / 2

    # Ap dung ham
    r1 = square(7)
    r2 = cube(4)
    r3 = double_v(21)
    r4 = add(100, 250)
    r5 = multiply(12, 15)
    r6 = average(88, 92)

    print(r1)
    print(r2)
    print(r3)
    print(r4)
    print(r5)
    print(r6)
}

@iter {
    # Rust-style iteration
    for i in 1..6 {
        print(i)
    }

    for i in 0..=4 {
        print(i)
    }

    # Lap toi khi dieu kien thoa
    while n > 5 {
        print(n)
        n = n - 1
    }

    # Loop voi break
    loop {
        print("Kiem tra dieu kien...")
        break
    }
}
