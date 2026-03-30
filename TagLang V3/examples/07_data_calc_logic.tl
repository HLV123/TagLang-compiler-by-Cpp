# ============================================================
#   FILE 07 — @data + @calc + @logic
#   Chu de: Tinh toan hoc phi va xep loai sinh vien
# ============================================================

@data {
    ten:        "Pham Minh Duc"
    tuoi:       20
    tin_chi:    18
    don_gia:    450000
    diem_toan:  85
    diem_ly:    78
    diem_anh:   92
    diem_tin:   88
    ho_tro:     true
    dem:        1
}

@calc {
    tong_diem    = diem_toan + diem_ly + diem_anh + diem_tin
    trung_binh   = tong_diem / 4
    hoc_phi      = tin_chi * don_gia
    gpa          = trung_binh / 25
    hoc_phi_thuc = hoc_phi - 500000
}

@logic {
    print("╔══════════════════════════════════╗")
    print("║   PHIEU TINH HOC PHI SINH VIEN   ║")
    print("╚══════════════════════════════════╝")
    print("Sinh vien : Pham Minh Duc")
    print("Tin chi   :")
    print(tin_chi)
    print("Hoc phi goc:")
    print(hoc_phi)

    if ho_tro == true then
        print(">>> Co ho tro hoc phi: -500,000 VND")
        print("Hoc phi thuc dong:")
        print(hoc_phi_thuc)
    else
        print("Hoc phi thuc dong:")
        print(hoc_phi)
    end

    print("--- Ket qua hoc tap ---")
    print("Trung binh:")
    print(trung_binh)
    print("GPA:")
    print(gpa)

    if trung_binh >= 90 then
        print("Xep loai: XUAT SAC")
    else
        if trung_binh >= 80 then
            print("Xep loai: GIOI")
        else
            if trung_binh >= 70 then
                print("Xep loai: KHA")
            else
                print("Xep loai: TRUNG BINH")
            end
        end
    end

    if gpa >= 3.5 then
        print(">>> Du dieu kien hoc bong!")
    else
        print(">>> Chua du dieu kien hoc bong.")
    end

    print("--- Dem mon dat (>= 80) ---")
    if diem_toan >= 80 then print("Toan: DAT") else print("Toan: CHUA DAT") end
    if diem_ly   >= 80 then print("Ly  : DAT") else print("Ly  : CHUA DAT") end
    if diem_anh  >= 80 then print("Anh : DAT") else print("Anh : DAT") end
    if diem_tin  >= 80 then print("Tin : DAT") else print("Tin : CHUA DAT") end
}
