# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
