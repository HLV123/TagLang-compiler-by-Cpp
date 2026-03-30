#   NEW 05 — @rscript + @iter + @lambda
#   Chu de: Xu ly du lieu thong ke voi functional programming
#   Label: 6 (R) + 12 (Rust) + 11 (C#)

@rscript {
    # Tap du lieu nhiet do (R-style)
    nhiet_do <- c(28, 31, 25, 33, 29, 27, 35)
    luong_mua <- c(12, 0, 45, 3, 8, 22, 0)
    do_am    <- c(72, 65, 88, 55, 70, 80, 60)

    # Gia tri thong ke
    nhiet_tb  <- 29.7
    nhiet_max <- 35
    nhiet_min <- 25
    so_ngay   <- 7

    print(nhiet_do)
    print(luong_mua)
    print(do_am)
    print(nhiet_tb)
    print(nhiet_max)
    print(nhiet_min)
}

@lambda {
    # Ham xu ly du lieu kieu C#
    to_fahrenheit  = x => x * 9 / 5 + 32
    is_rainy       = x => x > 10
    is_hot         = x => x >= 32
    heat_index     = (t, h) => t + h / 10
    comfort_score  = (t, h) => 100 - t - h / 5
    rain_risk      = (r, h) => r + h / 2

    # Tinh toan cho ngay nong nhat (35 do C, 60% do am)
    f35      = to_fahrenheit(35)
    hot_flag = is_hot(35)
    hi_35    = heat_index(35, 60)
    cs_35    = comfort_score(35, 60)
    rr_35    = rain_risk(0, 60)

    print(f35)
    print(hot_flag)
    print(hi_35)
    print(cs_35)
    print(rr_35)

    # Ngay lanh nhat (25 do C, 88% do am)
    f25   = to_fahrenheit(25)
    hi_25 = heat_index(25, 88)
    cs_25 = comfort_score(25, 88)

    print(f25)
    print(hi_25)
    print(cs_25)
}

@iter {
    print("=== Quet 7 ngay trong tuan ===")
    for day in 1..=7 {
        print(day)
    }

    print("=== Dem ngay nong (>= 30 do) ===")
    for hot_day in 1..=3 {
        print(hot_day)
    }

    print("=== Phan tich theo gio (0..23) ===")
    for hour in 0..6 {
        print(hour)
    }

    print("=== Watchdog thoi tiet ===")
    loop {
        print("Thu thap du lieu cam bien...")
        loop {
            print("Ket noi tram khi tuong...")
            break
        }
        break
    }

    print("=== Mua theo tuan (inclusive 1..7) ===")
    for w in 1..=5 {
        print(w)
    }
}
