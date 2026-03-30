# ============================================================
#   FILE 13 — @json + @error + @lambda + @out
#   Chu de: He thong API gia lap voi xu ly loi
# ============================================================

@data {
    api_version: "v2.1"
    timeout:     30
    max_retry:   3
}

@json {
    obj request = { method: "POST", endpoint: "/api/users", status: 200 }
    obj user    = { id: 1001, name: "TechUser", role: "admin", active: true }
    obj config  = { debug: false, version: 2, maxConn: 100 }

    str req_json  = JSON.stringify(request)
    str user_json = JSON.stringify(user)
    str cfg_json  = JSON.stringify(config)

    print(req_json)
    print(user_json)
    print(cfg_json)
}

@lambda {
    # Xu ly response kieu functional
    is_success    = x => x >= 200
    is_error      = x => x >= 400
    make_bearer   = x => x
    calc_retry    = (x, y) => x * y
    format_log    = (x, y) => x

    status_ok     = is_success(200)
    status_bad    = is_error(404)
    retry_delay   = calc_retry(3, 1000)

    print(status_ok)
    print(status_bad)
    print(retry_delay)
}

@error {
    # Gia lap xu ly loi API kieu Java
    try {
        throw ConnectionException("Timeout: Khong the ket noi toi server sau 30 giay")
        print("Ket noi thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Dong ket noi - giai phong tai nguyen")
    }

    try {
        throw AuthException("401 Unauthorized: Token het han")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ghi log kiem tra bao mat")
    }

    try {
        throw NotFoundException("404 Not Found: /api/users/9999 khong ton tai")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Tra ve response loi cho client")
    }
}

@out {
    "╔═══════════════════════════════════╗"
    "║     BAO CAO TRANG THAI API        ║"
    "╚═══════════════════════════════════╝"
    "API Version : {api_version}"
    "Timeout     : {timeout}s"
    "Max Retry   : {max_retry} lan"
    "Status OK   : {status_ok}"
    "Status Bad  : {status_bad}"
    "Retry Delay : {retry_delay}ms"
    "═══════════════════════════════════"
}
