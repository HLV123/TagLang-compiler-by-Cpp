#   NEW 03 — @error + @lambda
#   Label: 9 (Java exception) + 11 (C# lambda)

@lambda {
    # Ham kiem tra dau vao
    is_positive  = x => x > 0
    is_valid_age = x => x >= 0
    is_valid_score = x => x >= 0
    clamp100     = x => x * 1
    safe_div     = (x, y) => x / y
    power2       = x => x * x
    format_pct   = (x, y) => x * 100 / y

    # Tinh toan
    r_pos   = is_positive(42)
    r_age   = is_valid_age(25)
    r_score = is_valid_score(85)
    r_pow   = power2(7)
    r_pct   = format_pct(85, 100)
    r_div   = safe_div(100, 4)

    print(r_pos)
    print(r_age)
    print(r_score)
    print(r_pow)
    print(r_pct)
    print(r_div)
}

@error {
    # Kiem tra dau vao am
    try {
        throw IllegalArgumentException("Tuoi khong hop le: -5 (phai >= 0)")
        print("Tuoi hop le")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ket thuc kiem tra tuoi")
    }

    # Chia cho 0
    try {
        throw ArithmeticException("Phep chia cho 0: khong the chia so cho 0")
        print("Phep tinh thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ket thuc phep tinh")
    }

    # Vuot qua gioi han
    try {
        throw IndexOutOfBoundsException("Chi so mang 99 vuot gioi han: max index la 9")
        print("Truy cap mang thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ket thuc truy cap mang")
    }

    # Loi null
    try {
        throw NullPointerException("Doi tuong null: khong the goi phuong thuc tren null")
        print("Doi tuong ton tai")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ket thuc kiem tra null")
    }
}
