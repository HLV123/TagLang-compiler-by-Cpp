#   NEW 06 — @json + @ptr + @error
#   Chu de: Backend API + quan ly bo nho + xu ly ngoai le
#   Label: 7 (JS JSON) + 8 (Go/C ptr) + 9 (Java exception)

@json {
    # API Request/Response objects
    obj req_login  = { method: "POST", path: "/auth/login", status: 200 }
    obj req_data   = { method: "GET",  path: "/api/v2/data", status: 200 }
    obj req_upload = { method: "PUT",  path: "/api/v2/file", status: 201 }
    obj req_delete = { method: "DELETE", path: "/api/v2/item", status: 204 }

    # User session
    obj session = { userId: 9001, role: "admin", expires: 3600, active: true }

    # Database record
    obj db_record = { id: 42, table: "users", rows: 1250, indexed: true }

    # System health
    obj health = { cpu: 45, memory: 67, disk: 82, uptime: 99 }

    str login_str  = JSON.stringify(req_login)
    str data_str   = JSON.stringify(req_data)
    str sess_str   = JSON.stringify(session)
    str db_str     = JSON.stringify(db_record)
    str health_str = JSON.stringify(health)

    print(login_str)
    print(data_str)
    print(sess_str)
    print(db_str)
    print(health_str)
}

@ptr {
    # Quan ly trang thai server qua con tro (Go-style)
    var connections int = 0
    var requests    int = 0
    var errors      int = 0
    var latency_ms  int = 0

    var p_conn *int
    var p_req  *int
    var p_err  *int
    var p_lat  *int

    p_conn = &connections
    p_req  = &requests
    p_err  = &errors
    p_lat  = &latency_ms

    *p_conn = 247
    *p_req  = 15832
    *p_err  = 3
    *p_lat  = 42

    print(connections)
    print(requests)
    print(errors)
    print(latency_ms)
    print(*p_conn)
    print(*p_lat)

    func resetCounter(ptr *int) {
        *ptr = 0
    }

    func incrementBy100(ptr *int) {
        *ptr = 15932
    }

    resetCounter(&errors)
    print(errors)

    incrementBy100(&requests)
    print(requests)
}

@error {
    # Xu ly loi API phong cach Java
    try {
        throw AuthenticationException("401 Unauthorized: JWT token het han sau 3600 giay")
        print("Xac thuc thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Ghi audit log xac thuc")
    }

    try {
        throw RateLimitException("429 Too Many Requests: Vuot qua 100 req/giay")
        print("Request duoc xu ly")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Cap nhat rate limit counter")
    }

    try {
        throw DatabaseException("500 Internal Server Error: Connection pool exhausted (max: 50)")
        print("Ket noi database thanh cong")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Dong ket noi va tra ve pool")
    }

    try {
        throw ValidationException("400 Bad Request: Email khong dung dinh dang RFC 5322")
        print("Du lieu hop le")
    } catch (Exception e) {
        print(e)
    } finally {
        print("Tra ve response cho client")
    }
}
