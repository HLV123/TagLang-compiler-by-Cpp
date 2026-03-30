#   NEW 11 — 4 kieu bang trong TagLang
#   Labels: @data @calc @out @json @obj @array @iter

#   BANG 1: Bang ASCII dung @data + @calc + @out

@data {
    sv1:  "Nguyen Van A"
    d1t:  88
    d1l:  76
    d1a:  92
    sv2:  "Tran Thi B"
    d2t:  75
    d2l:  82
    d2a:  79
    sv3:  "Le Van C"
    d3t:  91
    d3l:  88
    d3a:  85
    sv4:  "Pham Thi D"
    d4t:  65
    d4l:  70
    d4a:  73
    so_hs: 4
}

@calc {
    tb1   = d1t + d1l + d1a
    tb2   = d2t + d2l + d2a
    tb3   = d3t + d3l + d3a
    tb4   = d4t + d4l + d4a
    tong  = tb1 + tb2 + tb3 + tb4
    tb_lp = tong / 4
}

@out {
    ""
    "========================================================"
    "  BANG 1: BANG DIEM HOC SINH  (@data + @calc + @out)"
    "========================================================"
    "+------------------+------+----+----+------+----------+"
    "| Ho Ten           | Toan | Ly | Anh| Tong | Xep loai |"
    "+------------------+------+----+----+------+----------+"
    "| {sv1}  | {d1t}   | {d1l} | {d1a} | {tb1} | Gioi     |"
    "| {sv2}   | {d2t}   | {d2l} | {d2a} | {tb2} | Kha      |"
    "| {sv3}     | {d3t}   | {d3l} | {d3a} | {tb3} | Gioi     |"
    "| {sv4}   | {d4t}   | {d4l} | {d4a} | {tb4} | TB       |"
    "+------------------+------+----+----+------+----------+"
    "  Tong: {so_hs} HS  |  Tong diem: {tong}  |  TB lop: {tb_lp}"
    "========================================================"
    ""
}

#   BANG 2: Bang JSON rows — moi object = 1 hang

@json {
    obj r1 = { ma: "SP001", ten: "Pho Bo",     gia: 85000, sl: 142 }
    obj r2 = { ma: "SP002", ten: "Bun Bo Hue", gia: 75000, sl: 98  }
    obj r3 = { ma: "SP003", ten: "Com Tam",    gia: 55000, sl: 210 }
    obj r4 = { ma: "SP004", ten: "Banh Mi",    gia: 35000, sl: 315 }
    obj r5 = { ma: "SP005", ten: "Nuoc Mia",   gia: 25000, sl: 420 }

    str s1 = JSON.stringify(r1)
    str s2 = JSON.stringify(r2)
    str s3 = JSON.stringify(r3)
    str s4 = JSON.stringify(r4)
    str s5 = JSON.stringify(r5)

    print(s1)
    print(s2)
    print(s3)
    print(s4)
    print(s5)
}

@out {
    "========================================================"
    "  BANG 2: BANG JSON OBJECT ROWS  (@json JS style)"
    "  Moi JSON object = 1 hang, stringify hien thi day du"
    "========================================================"
    "  {s1}"
    "  {s2}"
    "  {s3}"
    "  {s4}"
    "  {s5}"
    "========================================================"
    ""
}

#   BANG 3: Bang mang + vong lap — @array + @iter
@array {
    int thang[6]   = {1,   2,   3,   4,   5,   6  }
    int dt[6]      = {420, 385, 510, 465, 590, 625 }
    int cp[6]      = {280, 260, 310, 290, 350, 380 }
    char tieu_de[] = "BANG 3: BANG THONG KE  (@array + @iter)"
    char *don_vi   = "trieu VND"
}

@iter {
    print("")
    print(tieu_de)
    print("========================================")
    print("+-------+----------+-----------+-------+")
    print("| Thang | DT(trieu)| CP(trieu) | LN    |")
    print("+-------+----------+-----------+-------+")
    for i in 0..6 {
        print(thang[i])
        print(dt[i])
        print(cp[i])
    }
    print("+-------+----------+-----------+-------+")
    print("| TONG  | 2995     | 1870      | 1125  |")
    print("+-------+----------+-----------+-------+")
    print(don_vi)
    print("========================================")
    print("")
}

#   BANG 4: Bang key-value chi tiet — @obj (Ruby/Lua)
@obj {
    lp1 = { ten: "MacBook Pro",  cpu: "M3",  ram: "16GB", gia: "52tr" }
    lp2 = { ten: "Dell XPS 15",  cpu: "i9",  ram: "32GB", gia: "45tr" }
    lp3 = { ten: "iPad Pro",     cpu: "M2",  ram: "8GB",  gia: "28tr" }
    lp4 = { ten: "iPhone 15 Pro",cpu: "A17", ram: "8GB",  gia: "33tr" }

    print("")
    print("BANG 4: BANG KEY-VALUE OBJ  (@obj Ruby/Lua style)")
    print("Moi doi tuong = 1 hang, fields = cac cot")
    print("=========================================")
    print(lp1.ten)
    print(lp1.cpu)
    print(lp1.ram)
    print(lp1.gia)
    print(lp2.ten)
    print(lp2.cpu)
    print(lp2.ram)
    print(lp2.gia)
    print(lp3.ten)
    print(lp3.cpu)
    print(lp3.ram)
    print(lp3.gia)
    print(lp4.ten)
    print(lp4.cpu)
    print(lp4.ram)
    print(lp4.gia)
    print("=========================================")
}
