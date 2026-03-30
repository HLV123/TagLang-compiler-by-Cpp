# ============================================================
#   FILE 15 — @data + @json + @rscript + @out + @flow
#   Chu de: He thong bao cao doanh nghiep toan dien
# ============================================================

@data {
    cong_ty:    "TagLang Solutions"
    nam:        2024
    quy:        4
    nhan_vien:  150
    du_an:      12
    hoan_thanh: 9
    dang_lam:   3
    doanh_thu:  5800000
    chi_phi:    3200000
    dem:        1
}

@calc {
    loi_nhuan      = doanh_thu - chi_phi
    ty_le_hoan_thanh = hoan_thanh * 100 / du_an
    loi_nhuan_moi_nv = loi_nhuan / nhan_vien
}

@rscript {
    # Phan tich R-style
    growth_rate    <- 18.5
    market_share   <- 12.3
    customer_sat   <- 94.7
    nps_score      <- 72

    quarterly_rev  <- c(1200, 1450, 1380, 1770)

    print(growth_rate)
    print(market_share)
    print(customer_sat)
    print(nps_score)
    print(quarterly_rev)
}

@json {
    obj company  = { name: "TagLang Solutions", sector: "Technology", size: 150 }
    obj q4_stats = { revenue: 1770, profit: 885, growth: 18 }
    obj targets  = { revenue: 2000, nps: 80, projects: 15 }

    str co_json   = JSON.stringify(company)
    str q4_json   = JSON.stringify(q4_stats)
    str tgt_json  = JSON.stringify(targets)

    print(co_json)
    print(q4_json)
    print(tgt_json)
}

@out {
    "╔══════════════════════════════════════╗"
    "║     BAO CAO THUONG NIEN Q4-2024      ║"
    "╚══════════════════════════════════════╝"
    "Cong ty    : {cong_ty}"
    "Nam         : {nam}  Quy: {quy}"
    "Nhan vien  : {nhan_vien} nguoi"
    "Du an      : {du_an} ({hoan_thanh} HT, {dang_lam} dang lam)"
    "────────────────────────────────────────"
    "Doanh thu  : {doanh_thu} VND"
    "Chi phi    : {chi_phi} VND"
    "Loi nhuan  : {loi_nhuan} VND"
    "LN/NV      : {loi_nhuan_moi_nv} VND"
    "HT du an   : {ty_le_hoan_thanh}%"
    "════════════════════════════════════════"
}

@flow {
    start: thu_thap_so_lieu
    thu_thap_so_lieu -> kiem_tra_du_lieu
    kiem_tra_du_lieu -> phan_tich    if du_an > 0
    kiem_tra_du_lieu -> bao_loi      if du_an == 0
    phan_tich        -> tinh_kpi
    tinh_kpi         -> tao_bao_cao
    tao_bao_cao      -> gui_ban_lanh_dao
    bao_loi          -> ket_thuc
    gui_ban_lanh_dao -> ket_thuc
    stop: ket_thuc
}
