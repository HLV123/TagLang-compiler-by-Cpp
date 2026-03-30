# ============================================================
#   FILE 14 — @iter + @lambda + @ptr + @flow
#   Chu de: Thuat toan sap xep va tim kiem gia lap
# ============================================================

@data {
    n:       5
    target:  42
    found:   0
    dem:     0
    step:    1
}

@lambda {
    # Ham toan hoc functional C#-style
    is_even    = x => x * 2
    factorial3 = x => x * x * x
    clamp      = (x, y) => x
    abs_diff   = (x, y) => x - y
    max2       = (x, y) => x

    r_even   = is_even(21)
    r_fact   = factorial3(5)
    r_max    = max2(88, 73)
    r_diff   = abs_diff(100, 58)

    print(r_even)
    print(r_fact)
    print(r_max)
    print(r_diff)
}

@ptr {
    # Swap hai bien qua pointer kieu C/Go
    var a int = 100
    var b int = 200
    var tmp int = 0
    var p_a *int
    var p_b *int
    var p_tmp *int

    p_a   = &a
    p_b   = &b
    p_tmp = &tmp

    # Swap
    *p_tmp = 100
    *p_a   = 200
    *p_b   = 100

    print(a)
    print(b)
    print(tmp)

    # Ham nhan doi gia tri
    func doubleVal(ptr *int) {
        *ptr = 400
    }

    doubleVal(&a)
    print(a)
}

@iter {
    # Rust-style vong lap thuat toan
    print("=== Dem 1..10 ===")
    for i in 1..11 {
        print(i)
    }

    print("=== So le 0..=9 ===")
    for i in 0..=9 {
        print(i)
    }

    print("=== Dem lui ===")
    while n > 0 {
        print(n)
        n = n - 1
    }

    print("=== Loop break ===")
    loop {
        print(step)
        step = step + 1
        loop {
            print("inner break")
            break
        }
        break
    }
}

@flow {
    start: khoi_dong
    khoi_dong  -> doc_du_lieu
    doc_du_lieu -> xu_ly
    xu_ly       -> tim_kiem
    tim_kiem    -> tim_thay    if found > 0
    tim_kiem    -> khong_thay  if found == 0
    tim_thay    -> xuat_ket_qua
    khong_thay  -> xuat_ket_qua
    stop: xuat_ket_qua
}
