#   NEW 04 — @iter + @obj
#   Chu de: Duyet va thao tac doi tuong kieu Ruby/Lua + Rust
#   Label: 12 (Rust iter) + 13 (Ruby/Lua obj)


@obj {
    # Tao cac doi tuong Lua/Ruby style
    game = {}
    game.title   = "TagLang Quest"
    game.version = "1.0"
    game["genre"] = "RPG"
    game["level"] = "42"

    # Doi tuong nguoi choi
    player = { name: "Hero", hp: "100", mp: "50", gold: "999" }

    # Doi tuong quai vat
    enemy1 = { name: "Goblin",   hp: "30",  atk: "8",  xp: "15" }
    enemy2 = { name: "Orc",      hp: "80",  atk: "15", xp: "40" }
    enemy3 = { name: "Dragon",   hp: "500", atk: "50", xp: "200" }

    # Mang phan thuong (Lua 1-indexed)
    rewards = {10, 25, 50, 100, 250}

    # In thong tin
    print(game.title)
    print(game.version)
    print(game.genre)
    print(player.name)
    print(player.hp)
    print(player.gold)
    print(enemy1.name)
    print(enemy2.name)
    print(enemy3.name)
    print(rewards[1])
    print(rewards[5])

    # Ruby-style query
    has_title  = game.respond_to(title)
    is_table   = player.is_a(table)
    is_empty   = game.nil

    print(has_title)
    print(is_table)
    print(is_empty)
}

@iter {
    # Rust-style iteration
    print("=== Vong lap kem theo cap do ===")
    for level in 1..6 {
        print(level)
    }

    print("=== Dem phan thuong (inclusive) ===")
    for i in 1..=5 {
        print(i)
    }

    print("=== Dem nguoc HP ===")
    for hp_tick in 1..=5 {
        print(hp_tick)
    }

    print("=== Vong lap game (loop + break) ===")
    loop {
        print("Checking game state...")
        loop {
            print("Inner: Loading assets...")
            break
        }
        break
    }

    print("=== XP levels ===")
    for xp in 0..=4 {
        print(xp)
    }
}
