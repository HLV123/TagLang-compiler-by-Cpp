# ============================================================
#   TagLang Showcase — 5 label
# ============================================================

# ============================
#  LABEL 1: @data
#  Khai bao bien: string, int,
#  float, bool, array
# ============================
@data {
    ten:           "Tran Thi Bich"
    mssv:          20210001
    lop:           "CNTT-K21"
    toan:          88
    ly:            76
    hoa:           91
    van:           70
    gpa_target:    3.50
    da_tot_nghiep: false
    so_mon:        4
    dem:           1
}

# ============================
#  LABEL 2: @calc
#  Tinh toan: + - * / % ^
#  Luy thua ^ -> pow()
# ============================
@calc {
    tong_diem  = toan + ly + hoa + van
    trung_binh = tong_diem / 4
    gpa        = trung_binh / 25
    diem_sq    = trung_binh ^ 2
}

# ============================
#  LABEL 3: @out
#  In theo template {bien}
# ============================
@out {
    "============================================"
    "     PHIEU KET QUA HOC TAP SINH VIEN       "
    "============================================"
    "Ho ten  : {ten}"
    "MSSV    : {mssv}"
    "Lop     : {lop}"
    "--------------------------------------------"
    "Toan    : {toan}"
    "Ly      : {ly}"
    "Hoa     : {hoa}"
    "Van     : {van}"
    "--------------------------------------------"
    "Tong diem   : {tong_diem}"
    "Trung binh  : {trung_binh}"
    "GPA         : {gpa}"
    "GPA muc tieu: {gpa_target}"
    "TB binh phuong: {diem_sq}"
    "============================================"
}

# ============================
#  LABEL 4: @logic
#  if/else, while, repeat, print
#  Toan tu: == != < <= > >=
#           and or not
# ============================
@logic {
    # if/else long nhau
    print(">>> XEP LOAI HOC LUC:")
    if trung_binh >= 90 then
        print("    Xuat Sac")
    else
        if trung_binh >= 80 then
            print("    Gioi")
        else
            if trung_binh >= 65 then
                print("    Kha")
            else
                print("    Trung Binh")
            end
        end
    end

    # if don gian
    print(">>> KIEM TRA GPA MUC TIEU:")
    if gpa >= gpa_target then
        print("    Dat muc tieu!")
    else
        print("    Chua dat muc tieu.")
    end

    # while loop
    print(">>> DEM MON HOC (while):")
    while dem <= so_mon do
        print(dem)
        dem = dem + 1
    end

    # repeat
    print(">>> DONG VIEN (repeat):")
    repeat 3 times
        print("    Co gang len nhe!")
    end
}

# ============================
#  LABEL 5: @flow
#  So do luong thuc thi
#  nhan_A -> nhan_B [if dieu_kien]
# ============================
@flow {
    start: nop_ho_so
    nop_ho_so  -> kiem_tra
    kiem_tra   -> du_chuan  if trung_binh >= 50
    kiem_tra   -> hoc_lai   if trung_binh < 50
    du_chuan   -> hoc_bong  if gpa >= 3.50
    du_chuan   -> ra_truong
    hoc_bong   -> ra_truong
    stop: ra_truong, hoc_lai
}
