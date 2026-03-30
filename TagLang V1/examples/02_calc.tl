# TagLang Example 2 — Tính toán

@data {
    radius: 5
    height: 10
}

@calc {
    pi     = 3.14159
    area   = pi * radius * radius
    volume = area * height
}

@out {
    "=== Tinh toan hinh tru ==="
    "Ban kinh: {radius}"
    "Chieu cao: {height}"
    "Dien tich day: {area}"
    "The tich: {volume}"
}
