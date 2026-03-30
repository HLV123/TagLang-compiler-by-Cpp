# ============================================================
#   FILE 09 — @data + @rscript + @json + @array
#   Chu de: Phan tich du lieu khao sat sinh vien
# ============================================================

@data {
    khoa:       "CNTT"
    nam_hoc:    2024
    so_sv:      5
}

@rscript {
    # Dinh nghia du lieu kieu R
    diem_tb <- 8.2
    ty_le_dat <- 0.94
    so_gioi <- 12
    so_kha <- 18

    # Vector diem cac mon
    diem_mon <- c(85, 90, 78, 92, 88)

    print(diem_tb)
    print(ty_le_dat)
    print(so_gioi)
    print(diem_mon)
}

@json {
    obj sv1 = { name: "An",   score: 92, passed: true }
    obj sv2 = { name: "Binh", score: 78, passed: true }
    obj sv3 = { name: "Cuong",score: 55, passed: false }

    str s1 = JSON.stringify(sv1)
    str s2 = JSON.stringify(sv2)
    str s3 = JSON.stringify(sv3)

    print(s1)
    print(s2)
    print(s3)
}

@array {
    # Mang diem nguyen
    int scores[5] = {92, 78, 55, 88, 73}

    # Mang ky tu - ten mon hoc
    char mon1[] = "Lap Trinh C++"
    char mon2[] = "Co So Du Lieu"
    char mon3[] = "Mang May Tinh"
    char *mon4  = "Tri Tue Nhan Tao"
    char *mon5  = "Phat Trien Web"

    # In diem tung mon
    print(scores[0])
    print(scores[1])
    print(scores[2])
    print(scores[3])
    print(scores[4])

    # In ten mon
    print(mon1)
    print(mon2)
    print(mon3)
    print(mon4)
    print(mon5)
}
