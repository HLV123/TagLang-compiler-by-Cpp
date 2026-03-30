#   NEW 01 — @rscript + @json
#   Label: 6 (R) + 7 (JavaScript JSON)

@rscript {
    # Gia co phieu (R-style assignment)
    aapl  <- 182
    goog  <- 140
    msft  <- 375
    amzn  <- 178
    nvda  <- 875

    # Vector gia theo tuan
    tuan1 <- c(180, 182, 179, 185, 182)
    tuan2 <- c(175, 178, 182, 180, 183)

    # Ty le thay doi
    tang_truong <- 12.5
    bien_dong   <- 3.7
    vol_tb      <- 45000000

    print(aapl)
    print(goog)
    print(msft)
    print(amzn)
    print(nvda)
    print(tuan1)
    print(tuan2)
    print(tang_truong)
    print(bien_dong)
}

@json {
    obj aapl_info = { ticker: "AAPL", price: 182, sector: "Technology", rating: 5 }
    obj goog_info = { ticker: "GOOG", price: 140, sector: "Technology", rating: 4 }
    obj msft_info = { ticker: "MSFT", price: 375, sector: "Technology", rating: 5 }
    obj portfolio = { total: 1572, gain: 185, loss: 42, net: 143 }
    obj market    = { status: "BULL", vix: 14, trend: "UP", confidence: 85 }

    str aapl_str = JSON.stringify(aapl_info)
    str goog_str = JSON.stringify(goog_info)
    str msft_str = JSON.stringify(msft_info)
    str port_str = JSON.stringify(portfolio)
    str mkt_str  = JSON.stringify(market)

    print(aapl_str)
    print(goog_str)
    print(msft_str)
    print(port_str)
    print(mkt_str)
}
