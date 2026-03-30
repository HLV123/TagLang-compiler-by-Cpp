#   NEW 10 — TAT CA 8 LABEL MO RONG (6-13)
#   Label: @rscript @json @ptr @error @array @lambda @iter @obj

@rscript {
    # Doanh thu theo buoi (R-style)
    sang    <- 8500000
    trua    <- 15200000
    toi     <- 22800000
    tong_ngay <- 46500000

    # Mon an ban chay
    top_items <- c(1, 2, 3, 5, 8)
    gia_tb    <- c(85000, 120000, 95000, 75000, 150000)

    ty_le_khach_quay_lai <- 68.5
    diem_danh_gia        <- 4.7
    so_don_hom_nay       <- 142

    print(sang)
    print(trua)
    print(toi)
    print(tong_ngay)
    print(top_items)
    print(gia_tb)
    print(ty_le_khach_quay_lai)
    print(diem_danh_gia)
}

@json {
    obj restaurant = { name: "Pho Saigon", tables: 30, capacity: 120, rating: 5 }
    obj order1     = { id: 1001, table: 5,  items: 3, total: 285000, paid: true  }
    obj order2     = { id: 1002, table: 12, items: 5, total: 520000, paid: false }
    obj order3     = { id: 1003, table: 8,  items: 2, total: 170000, paid: true  }
    obj inventory  = { pho: 50, bun_bo: 35, com: 80, nuoc: 200, bia: 120 }

    str res_str = JSON.stringify(restaurant)
    str o1_str  = JSON.stringify(order1)
    str o2_str  = JSON.stringify(order2)
    str inv_str = JSON.stringify(inventory)

    print(res_str)
    print(o1_str)
    print(o2_str)
    print(inv_str)
}

@ptr {
    var ban_trong  int = 0
    var ban_co_khach int = 0
    var don_cho    int = 0
    var tong_hoa_don int = 0

    var p_tr  *int
    var p_ck  *int
    var p_cho *int
    var p_hd  *int

    p_tr  = &ban_trong
    p_ck  = &ban_co_khach
    p_cho = &don_cho
    p_hd  = &tong_hoa_don

    *p_tr  = 18
    *p_ck  = 12
    *p_cho = 5
    *p_hd  = 975000

    print(ban_trong)
    print(ban_co_khach)
    print(don_cho)
    print(tong_hoa_don)

    func serveTable(ptr *int) {
        *ptr = 11
    }

    func newOrder(ptr *int) {
        *ptr = 6
    }

    serveTable(&ban_trong)
    newOrder(&don_cho)

    print(ban_trong)
    print(don_cho)
}

@error {
    try {
        throw OutOfStockException("Het nguyen lieu: Pho bo chi con 2 phan, can nhap them")
        print("Nguyen lieu du")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Cap nhat trang thai kho nguyen lieu")
    }

    try {
        throw PaymentException("Thanh toan that bai: The tin dung bi tu choi - Ma loi: CARD_DECLINED")
        print("Thanh toan thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ghi log giao dich thanh toan")
    }

    try {
        throw KitchenException("Thiet bi bep loi: May giat bat hoat dong (nhiet do qua cao: 95C)")
        print("Thiet bi hoat dong binh thuong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Thong bao ky thuat vien bao tri")
    }
}

@array {
    int table_ids[8]  = {1, 2, 3, 4, 5, 6, 7, 8}
    int table_cap[8]  = {2, 2, 4, 4, 6, 6, 8, 10}
    int item_prices[6] = {85, 95, 120, 75, 150, 65}

    char menu1[]  = "Pho Bo Dac Biet"
    char menu2[]  = "Bun Bo Hue"
    char menu3[]  = "Com Tam Suon Bi"
    char *drink1   = "Nuoc Mia Viet Quat"
    char *drink2   = "Che Thai"
    char *special  = "Mon Dac Biet Hom Nay"

    print(table_ids[0])
    print(table_ids[7])
    print(table_cap[6])
    print(item_prices[0])
    print(item_prices[2])
    print(menu1)
    print(menu2)
    print(menu3)
    print(drink1)
    print(special)
}

@lambda {
    calc_tip      = (bill, pct) => bill * pct / 100
    apply_disc    = (bill, pct) => bill * (100 - pct) / 100
    split_bill    = (bill, n)   => bill / n
    vat_price     = x => x * 110 / 100
    member_price  = x => x * 90 / 100
    loyalty_pts   = x => x / 10000

    tip1  = calc_tip(520000, 10)
    disc1 = apply_disc(285000, 15)
    spl1  = split_bill(975000, 3)
    vat1  = vat_price(285000)
    mem1  = member_price(520000)
    pts1  = loyalty_pts(975000)

    print(tip1)
    print(disc1)
    print(spl1)
    print(vat1)
    print(mem1)
    print(pts1)
}

@iter {
    print("=== Quet 8 ban (0..8) ===")
    for t in 0..8 {
        print(t)
    }

    print("=== Ca lam viec (1..=3) ===")
    for shift in 1..=3 {
        print(shift)
    }

    print("=== Don cho dem nguoc ===")
    for waiting in 1..=5 {
        print(waiting)
    }

    print("=== POS system loop ===")
    loop {
        print("Nhan don hang moi...")
        loop {
            print("In hoa don...")
            break
        }
        break
    }

    print("=== Gio phuc vu (6..=10) ===")
    for h in 6..=10 {
        print(h)
    }
}

@obj {
    nha_hang = {}
    nha_hang.ten     = "Pho Saigon"
    nha_hang.dia_chi = "123 Nguyen Hue"
    nha_hang["dien_thoai"] = "0901234567"
    nha_hang["gio_mo"]     = "06:00-22:00"

    chinh_sach = { member_disc: "10%", loyalty: "1pt/10k", bday: "free_dessert" }
    danh_gia   = { sao: "4.7", binh_luan: "1250", xep_hang: "Top 10" }
    cap_do     = {1, 2, 3, 4, 5}

    print(nha_hang.ten)
    print(nha_hang.dia_chi)
    print(nha_hang.dien_thoai)
    print(chinh_sach.member_disc)
    print(chinh_sach.loyalty)
    print(danh_gia.sao)
    print(danh_gia.xep_hang)
    print(cap_do[1])
    print(cap_do[5])

    has_name   = nha_hang.respond_to(ten)
    is_table   = danh_gia.is_a(table)
    is_empty   = nha_hang.nil

    print(has_name)
    print(is_table)
    print(is_empty)
}
