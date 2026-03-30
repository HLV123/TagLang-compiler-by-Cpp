# TagLang Example 4 — Full Demo
# Kết hợp các @label

@data {
    student: "Nguyen Van A"
    math:    88
    physics: 75
    english: 92
}

@calc {
    total   = math + physics + english
    average = total / 3
}

@out {
    "=============================="
    "   BAO CAO KET QUA HOC TAP   "
    "=============================="
    "Ho ten : {student}"
    "Toan   : {math}"
    "Ly     : {physics}"
    "Anh    : {english}"
    "Tong   : {total}"
    "Trung binh: {average}"
}

@logic {
    if average >= 80 then
        print("=> Hoc sinh GIOI")
    else
        if average >= 65 then
            print("=> Hoc sinh KHA")
        else
            print("=> Hoc sinh TRUNG BINH")
        end
    end
}
