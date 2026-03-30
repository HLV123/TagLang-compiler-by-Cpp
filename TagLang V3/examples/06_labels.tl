# ============================================================
#   TagLang — Demo 13 label
# ============================================================

# === LABEL 1: @data ===
@data {
    ten:    "Nguyen Van A"
    tuoi:   21
    diem:   87
    active: true
    dem:    1
    so_lan: 3
}

# === LABEL 2: @calc ===
@calc {
    binh_phuong = diem ^ 2
    trung_binh  = diem / 10
}

# === LABEL 3: @logic ===
@logic {
    if diem >= 80 then
        print("Hoc luc: Gioi")
    else
        print("Hoc luc: Kha")
    end
    while dem <= 3 do
        print(dem)
        dem = dem + 1
    end
    repeat 2 times
        print("Chao!")
    end
}

# === LABEL 4: @out ===
@out {
    "=============================="
    "Ten  : {ten}  Tuoi: {tuoi}"
    "Diem : {diem} TB  : {trung_binh}"
    "=============================="
}

# === LABEL 5: @flow ===
@flow {
    start: nhan_don
    nhan_don  -> kiem_tra
    kiem_tra  -> chap_nhan if diem >= 60
    kiem_tra  -> tu_choi   if diem < 60
    stop: chap_nhan, tu_choi
}

# === LABEL 6: @rscript ===
@rscript {
    x <- 42
    name <- "TagLang"
    scores <- c(85, 90, 78, 92, 88)
    print(x)
    print(name)
}

# === LABEL 7: @json ===
@json {
    obj person = { name: "Alice", age: 30, score: 95 }
    str s = JSON.stringify(person)
    print(s)
}

# === LABEL 8: @ptr ===
@ptr {
    var px int = 10
    var pp *int
    pp = &px
    *pp = 99
    print(px)
    print(*pp)
    func zero(ptr *int) {
        *ptr = 0
    }
    zero(&px)
    print(px)
}

# === LABEL 9: @error ===
@error {
    try {
        throw RuntimeException("Co loi xay ra!")
        print("Dong nay khong chay")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Finally luon chay")
    }
}

# === LABEL 10: @array ===
@array {
    int arr[5] = {10, 20, 30, 40, 50}
    char str[] = "Hello TagLang"
    char *ptr = "Xin chao!"
    print(arr[0])
    print(arr[2])
    print(str)
    print(ptr)
}

# === LABEL 11: @lambda ===
@lambda {
    add    = (x, y) => x + y
    square = x => x * x
    greet  = () => "Hello from lambda!"
    result = add(10, 20)
    print(result)
    print(square(7))
    print(greet())
}

# === LABEL 12: @iter ===
@iter {
    for i in 0..5 {
        print(i)
    }
    for i in 0..=3 {
        print(i)
    }
    loop {
        print("loop runs once")
        break
    }
}

# === LABEL 13: @obj ===
@obj {
    t = {}
    t.name = "John"
    t["age"] = "30"
    person = { name: "Alice", city: "Hanoi" }
    oarr = {100, 200, 300}
    print(t.name)
    print(person.name)
    print(oarr[1])
    r = person.respond_to(name)
    print(r)
}
