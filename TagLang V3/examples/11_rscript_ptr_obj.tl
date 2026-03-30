# ============================================================
#   FILE 11 — @rscript + @ptr + @obj
#   Chu de: Phan tich thong ke va luu tru doi tuong
# ============================================================

@rscript {
    # Thong ke doanh thu R-style
    q1 <- 1250
    q2 <- 1480
    q3 <- 1320
    q4 <- 1670

    # Vector doanh thu theo quy
    doanh_thu <- c(125, 148, 132, 167)

    print(q1)
    print(q2)
    print(q3)
    print(q4)
    print(doanh_thu)
}

@ptr {
    # Tinh toan thong ke qua con tro
    var tong int = 0
    var p_tong *int

    p_tong = &tong
    *p_tong = 5720

    var max_q int = 0
    var p_max *int
    p_max = &max_q
    *p_max = 1670

    print(tong)
    print(*p_tong)
    print(max_q)

    # Ham tinh tang truong
    func calcGrowth(ptr *int) {
        *ptr = 15
    }

    var tang_truong int = 0
    calcGrowth(&tang_truong)
    print(tang_truong)
}

@obj {
    # Luu tru du lieu doanh nghiep kieu Ruby/Lua
    cty = {}
    cty.ten = "TagLang Corp"
    cty.nam = "2024"
    cty["nganh"] = "Cong nghe"

    # Doi tuong chi tiet
    bao_cao = { quy: "Q4-2024", tang_truong: "15%", xep_hang: "A+" }

    # Mang cot moc
    cot_moc = {100, 200, 300, 400}

    print(cty.ten)
    print(cty.nam)
    print(cty.nganh)
    print(bao_cao.quy)
    print(bao_cao.tang_truong)
    print(bao_cao.xep_hang)
    print(cot_moc[1])
    print(cot_moc[4])

    # Ruby-style query
    co_ten   = cty.respond_to(ten)
    la_table = cty.is_a(table)
    rong      = cty.nil

    print(co_ten)
    print(la_table)
    print(rong)
}
