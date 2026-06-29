# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [1.1.0] - 2026-06-30

### Added
- `--help`, `--version`, and `--batch` CLI flags (`src/main.c`)
- Non-interactive batch mode: reads `<type> <m3>` pairs from stdin,
  prints each bill, then prints a statistics summary (`src/main.c`)
- `src/version.h`: single source of truth for version string (`WBC_VERSION`)
- Commercial customer statistics: `commercial_count`, `commercial_revenue`,
  `max_commercial_bill` tracked in `Statistics` struct (`src/statistics.h/c`)
- `docs/tariff.md`: human-readable tariff reference with worked examples
- Makefile: `help`, `debug` (AddressSanitizer + UBSan), `install`,
  `uninstall` targets; `PREFIX`/`DESTDIR` support
- Test suite: `suite_stats_commercial` (10 new assertions → 97 total)

### Changed
- `0.95` waste-water fraction promoted to named constant
  `WASTE_WATER_FRACTION` in `billing.h`; removed magic literal from `billing.c`
- `print_bill()` no longer prints `VAT: 0.00 GBP` for domestic customers
- `stats_display()` output reformatted: section separators, per-type
  customer counts, conditional domestic/commercial max-bill lines
- Menu is now shown at the start of each interactive loop iteration
- Makefile variable `BINDIR` renamed to `BUILDDIR` (was: build output dir);
  `BINDIR` now follows the standard `$(PREFIX)/bin` convention

---

## [1.0.0] - 2026-06-30

### Added
- Core billing engine with domestic 5-tier progressive tariff (`src/billing.c`)
- Commercial flat-rate billing with 20 % VAT (`src/billing.c`)
- Quarterly statistics aggregation: revenue, cost, profit, income tax,
  maximum and average domestic bill (`src/statistics.c`)
- Interactive CLI with input validation (`src/main.c`)
- Full test suite — 87 assertions, zero external dependencies (`tests/test_all.c`)
- Minimal single-header test framework (`tests/test_framework.h`)
- Cross-platform `Makefile` (Linux, macOS, Windows/MSYS2)
- GitHub Actions CI on Linux (gcc + clang), macOS, and Windows/MinGW
- GitHub Actions automated release workflow (triggered by `v*.*.*` tags)
- Tri-lingual documentation: English, 简体中文, 日本語
- MIT License
