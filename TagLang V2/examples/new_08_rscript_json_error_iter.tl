#   NEW 08 — @rscript + @json + @error + @iter
#   Chu de: Phan tich du lieu y te + xu ly ngoai le + lap
#   Label: 6 (R) + 7 (JS) + 9 (Java) + 12 (Rust)

@rscript {
    # Du lieu benh nhan (R-style)
    tuoi     <- 45
    huyet_ap <- 135
    nhip_tim <- 88
    duong_huyet <- 6.8
    bmi      <- 27.4
    nhiet_do <- 37.2

    # Ket qua xet nghiem
    wbc  <- 7500
    rbc  <- 4800000
    hgb  <- 14.2
    plt  <- 250000

    # Lich su benh
    cholesterol <- c(185, 192, 205, 198, 201)
    glucozo     <- c(5.8, 6.1, 6.5, 6.8, 7.0)

    print(tuoi)
    print(huyet_ap)
    print(nhip_tim)
    print(duong_huyet)
    print(bmi)
    print(cholesterol)
    print(glucozo)
}

@json {
    obj patient  = { id: 20240001, age: 45, gender: "M", ward: "Cardiology" }
    obj vitals   = { bp: 135, hr: 88, temp: 37, bmi: 27, glucose: 6 }
    obj labs     = { wbc: 7500, rbc: 4800, hgb: 14, platelets: 250000 }
    obj medicine = { name: "Metformin", dose: 500, freq: 2, days: 30 }
    obj doctor   = { id: 5001, name: "Dr.Smith", specialty: "Internal" }

    str pat_str  = JSON.stringify(patient)
    str vit_str  = JSON.stringify(vitals)
    str lab_str  = JSON.stringify(labs)
    str med_str  = JSON.stringify(medicine)
    str doc_str  = JSON.stringify(doctor)

    print(pat_str)
    print(vit_str)
    print(lab_str)
    print(med_str)
    print(doc_str)
}

@error {
    try {
        throw HighBloodPressureException("Huyet ap cao: 135/85 mmHg - Tren nguong binh thuong 120/80")
        print("Huyet ap binh thuong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ghi nhat ky kham benh")
    }

    try {
        throw DiabetesRiskException("Duong huyet cao: 6.8 mmol/L - Nguong tien dai thao duong: 5.6-6.9")
        print("Duong huyet binh thuong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Tu van che do an uong")
    }

    try {
        throw OverweightException("BMI = 27.4: Thua can nhe (BMI binh thuong: 18.5 - 24.9)")
        print("Can nang binh thuong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Lap ke hoach giam can")
    }
}

@iter {
    print("=== Quet 5 lan do huyet ap ===")
    for reading in 1..=5 {
        print(reading)
    }

    print("=== Theo doi 7 ngay ===")
    for day in 0..7 {
        print(day)
    }

    print("=== Dem nguoc lich uong thuoc ===")
    for dose in 1..=5 {
        print(dose)
    }

    print("=== Vong kiem tra dau hieu sinh ton ===")
    loop {
        print("Do nhiet do...")
        loop {
            print("Do huyet ap...")
            break
        }
        break
    }

    print("=== Thang theo doi (1-12) ===")
    for month in 1..=5 {
        print(month)
    }
}
