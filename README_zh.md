# 水费账单计算器（Water Bill Calculator）

[![CI](https://github.com/frankwyf/water-bill-calculator/actions/workflows/ci.yml/badge.svg)](https://github.com/frankwyf/water-bill-calculator/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))

一个用于计算**居民用户**和**商业用户**季度水费账单的命令行工具，以可移植 C11 编写，无外部依赖。

> 🌐 其他语言版本：[English](README.md) | [日本語](README_ja.md)

---

## 功能特性

| 功能 | 说明 |
|---|---|
| 居民用水计费 | 5 档累进制新鲜水价；免征增值税 |
| 商业用水计费 | 新鲜水统一单价 + 20% 增值税 |
| 公共费用 | 污水处理费、地表水排水费、日常固定费用 |
| 季度统计 | 营业收入、成本、利润、25% 企业所得税、居民最高/平均账单 |
| 输入验证 | 拒绝负数用水量和无效用户类型 |
| 可移植性 | 遵循 C11 标准，无外部运行时依赖 |

## 快速开始

### 前置条件

| 平台 | 工具链 |
|---|---|
| Linux / macOS | `gcc` 或 `clang`，以及 `make` |
| Windows | 安装 [MSYS2](https://www.msys2.org/)，配置 `mingw-w64-x86_64-gcc` 和 `make` |

### 构建

```bash
make            # 生成 build/water_bill
```

### 运行

```bash
./build/water_bill
```

示例交互：

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

### 运行测试

```bash
make test       # 编译并运行完整测试套件
```

预期输出：

```
Results: 87 passed / 0 failed / 87 total
```

## 计费结构

### 居民用水

| 用水量（m³/季度） | 单价（GBP/m³） |
|---|---|
| 0 – 5 | 0.20 |
| 6 – 12 | 0.35 |
| 13 – 25 | 0.50 |
| 26 – 40 | 0.75 |
| > 40 | 2.50 |

季度固定附加费用：

- **污水处理费**：用水量的 95% × £0.25/m³
- **地表水排水费**：£10.00/季度
- **固定基本费**：£0.10/天 × 91 天 = £9.10
- **增值税**：0%（居民用户免税）

### 商业用水

- **新鲜水费**：£2.50/m³（统一单价）
- **污水处理费**：用水量的 95% × £2.00/m³
- **地表水排水费**：£50.00/季度
- **固定基本费**：£1.30/天 × 91 天 = £118.30
- **增值税**：按总费用的 20% 征收

## 项目结构

```
water-bill-calculator/
├── src/
│   ├── billing.h        # 费率常量、Bill 结构体、API 声明
│   ├── billing.c        # 账单计算实现
│   ├── statistics.h     # Statistics 结构体、API 声明
│   ├── statistics.c     # 季度统计汇总
│   └── main.c           # 交互式 CLI 入口
├── tests/
│   ├── test_framework.h # 极简零依赖测试宏框架
│   └── test_all.c       # 完整测试套件（87 个断言）
├── .github/
│   └── workflows/
│       ├── ci.yml       # 在 Linux、macOS、Windows 上构建并测试
│       └── release.yml  # 推送 tag 时自动发布 GitHub Release
├── Makefile
├── README.md            # English
├── README_zh.md         # 本文件（简体中文）
├── README_ja.md         # 日本語
├── LICENSE              # MIT 许可证
├── CHANGELOG.md
└── CONTRIBUTING.md
```

## 参与贡献

欢迎任何形式的贡献！请先阅读 [CONTRIBUTING.md](CONTRIBUTING.md)。

## 许可证

本项目遵循 **MIT 许可证**，详情请参阅 [LICENSE](LICENSE)。
