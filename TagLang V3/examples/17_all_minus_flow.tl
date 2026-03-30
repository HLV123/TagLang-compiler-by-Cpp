# ============================================================
#   FILE 17 — 12 label (tat ca tru @flow)
#   Chu de: He thong quan ly sinh vien toan dien
# ============================================================

@data {
    ten:     "Le Thi Mai"
    msv:     "SV2024001"
    lop:     "CNTT-K24"
    dem:     1
    bac_hoc: 1
}

@calc {
    diem_tong  = 85 + 78 + 92 + 88 + 76
    diem_tb    = diem_tong / 5
    gpa_4      = diem_tb / 25
    tin_chi    = 20
    hoc_phi    = tin_chi * 450000
}

@logic {
    print("=== KIEM TRA XEP LOAI ===")
    if diem_tb >= 90 then
        print("Xuat sac")
    else
        if diem_tb >= 80 then
            print("Gioi")
        else
            print("Kha")
        end
    end

    while dem <= 3 do
        print(dem)
        dem = dem + 1
    end

    repeat 2 times
        print("Thong bao!")
    end
}

@out {
    "╔════════════════════════════════╗"
    "║    HO SO SINH VIEN             ║"
    "╚════════════════════════════════╝"
    "Ten  : {ten}"
    "MSV  : {msv}   Lop: {lop}"
    "TB   : {diem_tb}   GPA: {gpa_4}"
    "HP   : {hoc_phi} VND"
    "════════════════════════════════"
}

@rscript {
    diem_mon <- c(85, 78, 92, 88, 76)
    tb_thuc  <- 83.8
    rank     <- 12
    print(diem_mon)
    print(tb_thuc)
    print(rank)
}

@json {
    obj sinhvien = { name: "Le Thi Mai", gpa: 3, year: 1 }
    obj diem_chi = { ly_thuyet: 80, thuc_hanh: 90, cuoi_ky: 85 }
    str sv_json  = JSON.stringify(sinhvien)
    str dc_json  = JSON.stringify(diem_chi)
    print(sv_json)
    print(dc_json)
}

@ptr {
    var gpa_int int = 0
    var p_gpa *int
    p_gpa = &gpa_int
    *p_gpa = 3
    print(gpa_int)
    print(*p_gpa)
    func bump(ptr *int) {
        *ptr = 4
    }
    bump(&gpa_int)
    print(gpa_int)
}

@error {
    try {
        throw ValidationException("GPA khong hop le: am hoac > 4.0")
        print("Du lieu hop le")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ket thuc kiem tra du lieu")
    }
}

@array {
    int grades[5]  = {85, 78, 92, 88, 76}
    char major[]   = "Cong Nghe Thong Tin"
    char *school   = "Dai Hoc Bach Khoa"
    print(grades[0])
    print(grades[4])
    print(major)
    print(school)
}

@lambda {
    pass_check = x => x >= 50
    honor_check = x => x >= 85
    grade_calc = (x, y) => x + y

    r1 = pass_check(78)
    r2 = honor_check(85)
    r3 = grade_calc(85, 78)

    print(r1)
    print(r2)
    print(r3)
}

@iter {
    for i in 0..5 {
        print(i)
    }
    for i in 1..=3 {
        print(i)
    }
    loop {
        print("Kiem tra xong!")
        break
    }
}

@obj {
    sv = {}
    sv.ten = "Le Thi Mai"
    sv["gpa"] = "3.35"
    info = { ten: "Mai", lop: "K24", gpa: "3.35" }
    print(sv.ten)
    print(sv.gpa)
    print(info.ten)
    print(info.lop)
    co_ten = info.respond_to(ten)
    print(co_ten)
}
