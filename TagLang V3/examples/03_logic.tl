# TagLang Example 3 — Logic
# Minh họa @logic: if/else, while, repeat

@data {
    score: 85
    count: 5
}

@logic {
    # Kiểm tra điểm
    if score >= 90 then
        print("Xep loai: Xuat sac")
    else
        if score >= 75 then
            print("Xep loai: Gioi")
        else
            print("Xep loai: Trung binh")
        end
    end

    # Đếm ngược
    print("--- Dem nguoc ---")
    while count > 0 do
        print(count)
        count = count - 1
    end

    # Lặp lại
    print("--- Lap lai ---")
    repeat 3 times
        print("TagLang!")
    end
}
