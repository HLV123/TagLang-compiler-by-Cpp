#   NEW 09 — @ptr + @lambda + @iter + @obj
#   Label: 8 (Go ptr) + 11 (C# lambda) + 12 (Rust iter) + 13 (Lua obj)

@obj {
    # Doi tuong game kieu Lua
    world = {}
    world.name   = "Shadow Realm"
    world.width  = "1920"
    world.height = "1080"
    world["gravity"] = "9.8"
    world["fps"]     = "60"

    hero = { name: "Shadow Knight", class: "Warrior", level: "15", hp: "450" }
    npc1 = { name: "Merchant",  role: "shop",   gold: "9999", items: "50" }
    npc2 = { name: "Blacksmith",role: "craft",  gold: "500",  items: "30" }
    npc3 = { name: "Guard",     role: "protect",gold: "100",  items: "5"  }

    inventory = {50, 100, 200, 500, 1000}

    print(world.name)
    print(world.width)
    print(world.fps)
    print(hero.name)
    print(hero.class)
    print(hero.level)
    print(npc1.name)
    print(npc2.name)
    print(npc3.name)
    print(inventory[1])
    print(inventory[5])

    has_name  = world.respond_to(name)
    is_world  = world.is_a(table)
    print(has_name)
    print(is_world)
}

@ptr {
    # Trang thai game qua con tro (Go-style)
    var pos_x   int = 0
    var pos_y   int = 0
    var vel_x   int = 0
    var vel_y   int = 0
    var hp      int = 450
    var mp      int = 200
    var score   int = 0

    var p_x  *int
    var p_y  *int
    var p_hp *int
    var p_mp *int
    var p_sc *int

    p_x  = &pos_x
    p_y  = &pos_y
    p_hp = &hp
    p_mp = &mp
    p_sc = &score

    *p_x  = 320
    *p_y  = 240
    *p_hp = 380
    *p_mp = 150
    *p_sc = 7500

    print(pos_x)
    print(pos_y)
    print(hp)
    print(mp)
    print(score)

    func takeDamage(ptr *int) {
        *ptr = 305
    }

    func gainScore(ptr *int) {
        *ptr = 7700
    }

    func useMana(ptr *int) {
        *ptr = 100
    }

    takeDamage(&hp)
    gainScore(&score)
    useMana(&mp)

    print(hp)
    print(score)
    print(mp)
}

@lambda {
    # Ham vat ly game C#-style
    calc_damage  = (atk, def) => atk - def
    calc_heal    = (hp, max) => hp + 50
    is_alive     = x => x > 0
    critical_hit = x => x * 2
    xp_to_level  = x => x * 100
    move_speed   = (base, buff) => base + buff

    dmg1  = calc_damage(75, 20)
    dmg2  = critical_hit(75)
    alive = is_alive(305)
    xp15  = xp_to_level(15)
    spd   = move_speed(5, 3)

    print(dmg1)
    print(dmg2)
    print(alive)
    print(xp15)
    print(spd)
}

@iter {
    print("=== Game loop (5 frames) ===")
    for frame in 1..=5 {
        print(frame)
    }

    print("=== Danh sach ky nang (0..7) ===")
    for skill in 0..8 {
        print(skill)
    }

    print("=== HP tick countdown ===")
    for tick in 1..=5 {
        print(tick)
    }

    print("=== Main game loop ===")
    loop {
        print("Update physics...")
        loop {
            print("Render frame...")
            break
        }
        break
    }

    print("=== Level milestones (1..=5) ===")
    for lv in 1..=5 {
        print(lv)
    }
}
