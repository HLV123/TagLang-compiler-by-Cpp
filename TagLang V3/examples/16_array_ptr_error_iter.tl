# ============================================================
#   FILE 16 — @array + @ptr + @error + @iter
#   Chu de: Quan ly mang bo nho va xu ly ngoai le
# ============================================================

@array {
    # Mang du lieu cam bien IoT
    int sensor[8]  = {22, 35, 18, 41, 29, 37, 15, 33}
    int thresh[3]  = {20, 30, 40}
    char c_low[]   = "THAP"
    char c_norm[]  = "BINH THUONG"
    char *c_high   = "CAO"
    char *c_crit   = "NGUY HIEM"
    char device[]  = "IoT Sensor Array v1.0"

    print(device)
    print(sensor[0])
    print(sensor[3])
    print(sensor[6])
    print(c_low)
    print(c_norm)
    print(c_high)
    print(c_crit)
}

@ptr {
    # Quan ly bien trang thai qua con tro
    var current_temp int = 0
    var alert_level  int = 0
    var p_temp *int
    var p_alert *int

    p_temp  = &current_temp
    p_alert = &alert_level

    *p_temp  = 41
    *p_alert = 3

    print(current_temp)
    print(alert_level)
    print(*p_temp)

    func normalize(ptr *int) {
        *ptr = 25
    }

    normalize(&current_temp)
    print(current_temp)
}

@error {
    # Xu ly ngoai le cam bien
    try {
        throw SensorException("Cam bien #4 vuot nguong NGUY HIEM: 41 do C")
        print("Doc du lieu cam bien thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ghi nhat ky cam bien")
    }

    try {
        throw MemoryException("Tran bo nho dem cam bien: 256 byte > 128 byte cho phep")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Giai phong bo nho tam")
    }

    try {
        throw TimeoutException("Cam bien #7 khong phan hoi sau 5000ms")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Reset cam bien va thu lai")
    }
}

@iter {
    print("=== Quet tat ca cam bien ===")
    for i in 0..8 {
        print(i)
    }

    print("=== Kiem tra cam bien uu tien cao ===")
    for i in 0..=2 {
        print(i)
    }

    print("=== Dem nguoc canhbao ===")
    while alert_level > 0 {
        print(alert_level)
        alert_level = alert_level - 1
    }

    print("=== Watchdog loop ===")
    loop {
        print("Watchdog: He thong on dinh")
        break
    }
}
