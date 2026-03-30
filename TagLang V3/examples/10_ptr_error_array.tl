# ============================================================
#   FILE 10 — @ptr + @error + @array
#   Chu de: Quan ly bo nho kieu C/Go + xu ly loi Java
# ============================================================

@array {
    # Mang so nguyen
    int temps[7] = {28, 31, 27, 33, 29, 35, 30}
    char label[] = "Nhiet do 7 ngay (do C)"
    char *unit   = "do Celsius"

    print(label)
    print(temps[0])
    print(temps[1])
    print(temps[2])
    print(temps[3])
    print(temps[4])
    print(temps[5])
    print(temps[6])
    print(unit)
}

@ptr {
    # Khai bao bien va con tro kieu Go
    var nhiet_max int = 0
    var nhiet_min int = 99
    var p_max *int
    var p_min *int

    p_max = &nhiet_max
    p_min = &nhiet_min

    # Cap nhat gia tri qua con tro
    *p_max = 35
    *p_min = 27

    print(nhiet_max)
    print(nhiet_min)
    print(*p_max)
    print(*p_min)

    # Ham reset qua pointer
    func resetVal(ptr *int) {
        *ptr = 0
    }

    resetVal(&nhiet_max)
    print(nhiet_max)
}

@error {
    # Xu ly loi kieu Java
    try {
        throw RuntimeException("Nhiet do vuot nguong an toan: 35 do C!")
        print("Cam bien hoat dong binh thuong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("He thong giam sat ket thuc phien doc")
    }

    # Thu nghiem mot loi khac
    try {
        throw IllegalArgumentException("Chi so cam bien khong hop le: -1")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ket thuc kiem tra cam bien")
    }
}
