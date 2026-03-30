#   NEW 07 — @array + @lambda + @obj
#   Label: 10 (C array) + 11 (C# lambda) + 13 (Ruby/Lua obj)

@array {
    # Mang du lieu san pham
    int prices[6]    = {299, 499, 799, 149, 999, 599}
    int quantities[6] = {50, 30, 20, 100, 15, 45}
    int ratings[6]   = {4, 5, 3, 4, 5, 4}

    char prod1[] = "Laptop Basic"
    char prod2[] = "Laptop Pro"
    char prod3[] = "Laptop Ultra"
    char *brand1  = "TechBrand A"
    char *brand2  = "TechBrand B"
    char *brand3  = "TechBrand C"

    print(prices[0])
    print(prices[1])
    print(prices[2])
    print(quantities[0])
    print(ratings[1])
    print(ratings[4])
    print(prod1)
    print(prod2)
    print(prod3)
    print(brand1)
    print(brand2)
    print(brand3)
}

@lambda {
    # Ham tinh toan san pham C#-style
    total_value    = (p, q) => p * q
    discount_10    = x => x * 9 / 10
    discount_20    = x => x * 8 / 10
    apply_tax      = x => x * 11 / 10
    is_expensive   = x => x >= 500
    profit_margin  = (sell, cost) => sell - cost
    rating_good    = x => x >= 4

    # Laptop Basic
    tv1  = total_value(299, 50)
    d1   = discount_10(299)
    tx1  = apply_tax(299)
    exp1 = is_expensive(299)

    # Laptop Pro
    tv2  = total_value(499, 30)
    d2   = discount_20(499)
    exp2 = is_expensive(499)

    # Laptop Ultra
    tv3  = total_value(799, 20)
    d3   = discount_20(799)
    pm3  = profit_margin(799, 550)

    print(tv1)
    print(d1)
    print(tx1)
    print(exp1)
    print(tv2)
    print(d2)
    print(exp2)
    print(tv3)
    print(d3)
    print(pm3)
}

@obj {
    # Catalog san pham kieu Lua/Ruby
    catalog = {}
    catalog.name    = "Tech Store 2024"
    catalog.items   = "6"
    catalog["currency"] = "USD"
    catalog["tax_rate"] = "10%"

    laptop_basic = { name: "Laptop Basic", price: "299", stock: "50", brand: "TechBrand A" }
    laptop_pro   = { name: "Laptop Pro",   price: "499", stock: "30", brand: "TechBrand B" }
    laptop_ultra = { name: "Laptop Ultra", price: "799", stock: "20", brand: "TechBrand C" }

    # Best seller list (Lua array)
    bestsellers = {1, 2, 3}

    print(catalog.name)
    print(catalog.items)
    print(catalog.currency)
    print(laptop_basic.name)
    print(laptop_basic.price)
    print(laptop_pro.name)
    print(laptop_ultra.name)
    print(laptop_ultra.price)
    print(bestsellers[1])
    print(bestsellers[3])

    has_name   = catalog.respond_to(name)
    is_catalog = catalog.is_a(table)
    is_empty   = catalog.nil

    print(has_name)
    print(is_catalog)
    print(is_empty)
}
