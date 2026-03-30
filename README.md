# TagLang

Một compiler đồ chơi viết bằng C++17, dịch ngôn ngữ tự thiết kế sang C++.

---

## Về project này

TagLang là một **sản phẩm demo nhỏ**, không có tham vọng trở thành ngôn ngữ lập trình thực thụ. Mục đích chính là **tham khảo cách tổ chức một compiler đơn giản bằng C++** — từ Lexer, Parser, AST đến Code Generation.

Nếu bạn đang học C++ và muốn xem cách:
- Xây dựng **Lexer** (tách token từ source code)
- Thiết kế **AST** (Abstract Syntax Tree)
- Viết **Parser** theo kiểu module (mỗi tính năng = 1 parser riêng)
- Sinh **C++ code** từ AST

...thì đây là một ví dụ nhỏ, dễ đọc, không quá phức tạp.

---

## Ý tưởng

TagLang có một đặc trưng: **mỗi `@label` mở ra một cú pháp riêng**, lấy cảm hứng từ các ngôn ngữ lập trình khác nhau.

```taglang
@data    { ten: "Alice"  tuoi: 20 }          # khai báo biến
@calc    { tb = (a + b) / 2 }               # tính toán
@logic   { if tb >= 80 then print("Giỏi") end }
@out     { "Tên: {ten} — Điểm TB: {tb}" }   # template output

@rscript { scores <- c(85, 90, 78) }        # R Language style
@json    { obj p = { name: "Alice" } }       # JavaScript style
@ptr     { var x int = 10  var p *int }      # Go/C style
@error   { try { ... } catch (Exception e) { ... } }  # Java style
@lambda  { add = (x, y) => x + y }          # C# style
@iter    { for i in 0..10 { print(i) } }    # Rust style
@func    { func square(x) { return x*x } }  # hàm người dùng
```

Compiler dịch file `.tl` → `.cpp` → binary chạy được.

---

## Kiến trúc

```
TagLang/
├── src/
│   ├── lexer.h / lexer.cpp          ← Tokenizer
│   ├── label_dispatcher.h           ← Điều phối @label → parser
│   ├── ast/ast_nodes.h              ← Định nghĩa AST
│   ├── parsers/                     ← Mỗi @label = 1 parser
│   │   ├── base_parser.h
│   │   ├── data_parser.h
│   │   ├── logic_parser.h
│   │   └── ...
│   └── codegen/cpp_generator.h      ← Sinh C++ từ AST
└── examples/                        ← File .tl mẫu
```

Điểm đáng chú ý nhất là kiến trúc **module parser**: mỗi `@label` có một parser riêng kế thừa `BaseParser`. Muốn thêm cú pháp mới chỉ cần thêm 1 file, không đụng vào code cũ.

---

## Build & Chạy

Yêu cầu: `g++` (MinGW trên Windows)

```bat
# Build compiler
g++ -std=c++17 -O2 src\main.cpp -o taglang.exe

# Chạy thử
.\run.bat examples\06_all_labels.tl
```

---

## Trạng thái hiện tại

**Đã có (v3.0):**
- 14 label với cú pháp từ 8 ngôn ngữ khác nhau
- Compiler hoàn chỉnh: Lexer → Parser → AST → C++ codegen
- ~30 file ví dụ

**Chưa có — nếu có điều kiện muốn làm thêm:**
- `@string` — thao tác chuỗi (split, trim, replace, regex...)
- `@math` — các hàm toán học nâng cao (sin, cos, log, matrix...)
- `@file` — đọc/ghi file, xử lý CSV
- Interpreter thay vì transpiler (chạy trực tiếp không cần g++)
- VS Code extension để highlight cú pháp `.tl`
- Error messages thân thiện hơn (chỉ đúng dòng, đúng cột)

---

## Giấy phép

Tự do dùng để học, tham khảo, hoặc nghịch ngợm.

---

*Viết bằng C++17. Không có dependency ngoài. Build một lệnh.*
