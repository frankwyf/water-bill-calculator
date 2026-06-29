# Water Bill Calculator

[![CI](https://github.com/frankwyf/water-bill-calculator/actions/workflows/ci.yml/badge.svg)](https://github.com/frankwyf/water-bill-calculator/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))

A command-line quarterly water-bill calculator for **domestic** and **commercial** customers, written in portable C11.

> 🌐 Also available in: [中文](README_zh.md) | [日本語](README_ja.md)

---

## Features

| Feature | Detail |
|---|---|
| Domestic billing | 5-tier progressive fresh-water tariff; VAT-exempt |
| Commercial billing | Flat-rate fresh water + 20 % VAT |
| Shared charges | Waste water, surface water, daily standing charge |
| Quarterly statistics | Revenue, cost, profit, 25 % income tax, max/average domestic bill |
| Input validation | Rejects negative consumption and invalid customer type |
| Portable | C11, no external runtime dependencies |

## Quick Start

### Prerequisites

| Platform | Toolchain |
|---|---|
| Linux / macOS | `gcc` or `clang`, `make` |
| Windows | [MSYS2](https://www.msys2.org/) with `mingw-w64-x86_64-gcc` and `make` |

### Build

```bash
make            # produces build/water_bill
```

### Run

```bash
./build/water_bill
```

Sample session:

```
===========================================
         Water Bill Calculator
===========================================
  1. Compute and display a customer bill
  2. Display quarterly statistics
  3. Quit
===========================================

Enter your choice (1-3): 1
Customer type  (1=Domestic, 2=Commercial): 1
Water consumption (m3): 20
------------------------------------------
Customer Type:        Domestic
Water Consumption:    20 m3
Fresh Water Charge:   7.45 GBP
Waste Water Charge:   4.75 GBP
Surface Water Charge: 10.00 GBP
Standing Charge:      9.10 GBP
Total Charge:         31.30 GBP
VAT:                  0.00 GBP
Amount to Pay:        31.30 GBP
------------------------------------------
```

### Test

```bash
make test       # builds and runs the full test suite
```

Expected output:

```
Results: 87 passed / 0 failed / 87 total
```

## Tariff Structure

### Domestic

| Consumption (m³/quarter) | Rate (GBP/m³) |
|---|---|
| 0 – 5 | 0.20 |
| 6 – 12 | 0.35 |
| 13 – 25 | 0.50 |
| 26 – 40 | 0.75 |
| > 40 | 2.50 |

Additional quarterly charges:

- **Waste water**: 95 % of consumption × £0.25/m³
- **Surface water drainage**: £10.00/quarter
- **Standing charge**: £0.10/day × 91 days = £9.10
- **VAT**: 0 % (domestic customers are exempt)

### Commercial

- **Fresh water**: £2.50/m³ (flat rate)
- **Waste water**: 95 % of consumption × £2.00/m³
- **Surface water drainage**: £50.00/quarter
- **Standing charge**: £1.30/day × 91 days = £118.30
- **VAT**: 20 % applied to the total charge

## Project Structure

```
water-bill-calculator/
├── src/
│   ├── billing.h        # Tariff constants, Bill struct, API
│   ├── billing.c        # Bill computation
│   ├── statistics.h     # Statistics struct, API
│   ├── statistics.c     # Quarterly statistics aggregation
│   └── main.c           # Interactive CLI entry point
├── tests/
│   ├── test_framework.h # Minimal zero-dependency test macros
│   └── test_all.c       # Full test suite (87 assertions)
├── .github/
│   └── workflows/
│       ├── ci.yml       # Build + test on Linux, macOS, Windows
│       └── release.yml  # Create GitHub Release on tag push
├── Makefile
├── README.md            # This file (English)
├── README_zh.md         # 简体中文
├── README_ja.md         # 日本語
├── LICENSE              # MIT
├── CHANGELOG.md
└── CONTRIBUTING.md
```

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) first.

## License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE) for details.
