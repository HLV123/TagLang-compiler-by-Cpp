# ============================================================
#   FILE 08 — @calc + @logic + @out + @flow
#   Chu de: He thong tinh luong nhan vien
# ============================================================

@data {
    ten:          "Nguyen Thi Lan"
    chuc_vu:      "Senior Dev"
    luong_co_ban: 20000000
    so_ngay_lam:  22
    ngay_thuc_lam: 20
    thue_suat:    10
    thue_nguong:  11000000
    phat:         0
    dem:          1
}

@calc {
    luong_thuc    = luong_co_ban * ngay_thuc_lam / so_ngay_lam
    thue_tndn     = luong_thuc * thue_suat / 100
    luong_net     = luong_thuc - thue_tndn - phat
    hieu_suat     = ngay_thuc_lam * 100 / so_ngay_lam
    thuong        = luong_co_ban * 2
}

@out {
    "╔═══════════════════════════════════╗"
    "║      BANG TINH LUONG THANG        ║"
    "╚═══════════════════════════════════╝"
    "Nhan vien  : {ten}"
    "Chuc vu    : {chuc_vu}"
    "Luong CB   : {luong_co_ban} VND"
    "Ngay lam   : {ngay_thuc_lam}/{so_ngay_lam}"
    "Hieu suat  : {hieu_suat}%"
    "───────────────────────────────────"
    "Luong thuc : {luong_thuc} VND"
    "Thue TNCN  : {thue_tndn} VND"
    "Luong NET  : {luong_net} VND"
    "───────────────────────────────────"
}

@logic {
    if hieu_suat >= 100 then
        print(">>> Hieu suat: XUAT SAC - Thuong:")
        print(thuong)
    else
        if hieu_suat >= 90 then
            print(">>> Hieu suat: TOT")
        else
            if hieu_suat >= 80 then
                print(">>> Hieu suat: DAT YEU CAU")
            else
                print(">>> Hieu suat: CAN CAI THIEN")
            end
        end
    end

    if luong_net >= thue_nguong then
        print(">>> Phai dong thue thu nhap ca nhan")
    else
        print(">>> Mien thue thu nhap ca nhan")
    end
}

@flow {
    start: nhan_cham_cong
    nhan_cham_cong -> tinh_luong
    tinh_luong     -> kiem_tra_thue
    kiem_tra_thue  -> khau_tru_thue  if luong_thuc >= 11000000
    kiem_tra_thue  -> mien_thue      if luong_thuc < 11000000
    khau_tru_thue  -> xuat_phieu
    mien_thue      -> xuat_phieu
    stop: xuat_phieu
}
