# TagLang v3.0 — Test tất cả 5 fix

# FIX 1: @iter gán biến mới
@iter {
    dem = 0
    for i in 1..=5 {
        dem = dem + 1
        print(dem)
    }
    n = 10
    while n > 7 {
        print(n)
        n = n - 1
    }
}

# FIX 2: @obj print_row in nhiều cột
@obj {
    row1 = { ten: "Alice", diem: "95", xep_loai: "Gioi" }
    row2 = { ten: "Bob",   diem: "78", xep_loai: "Kha"  }
    row3 = { ten: "Carol", diem: "88", xep_loai: "Gioi" }
    print("| ten       | diem | xep_loai |")
    print("|-----------|------|----------|")
    print_row(row1)
    print_row(row2)
    print_row(row3)
}

# FIX 3: @rscript vector dùng được trong @out
@rscript {
    scores <- c(85, 90, 78, 92, 88)
    names  <- c(1, 2, 3, 4, 5)
    print(scores)
    print(names)
}

@out {
    "Diem: {scores_str}"
    "STT : {names_str}"
}

# FIX 4: @func — hàm người dùng tự định nghĩa
@func {
    func add(x, y) {
        return x + y
    }
    func square(x) {
        return x * x
    }
    func greet() {
        return "Xin chao tu TagLang v3!"
    }
    func bmi(w, h) {
        return w / (h * h)
    }

    r1 = add(10, 25)
    r2 = square(7)
    r3 = bmi(60, 2)

    print(r1)
    print(r2)
    print(r3)
    print(greet())
}

# FIX 5: Tránh trùng tên biến — dùng @data + @rscript cùng tên
@data {
    x: 100
    y: 200
}

@rscript {
    x <- 999
    print(x)
}

@out {
    "x tu @data: {x}"
}
