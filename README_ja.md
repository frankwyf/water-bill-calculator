# 水道料金計算機（Water Bill Calculator）

[![CI](https://github.com/frankwyf/water-bill-calculator/actions/workflows/ci.yml/badge.svg)](https://github.com/frankwyf/water-bill-calculator/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))

家庭用および商業用の顧客向け、四半期ごとの水道料金を計算するコマンドライン（CLI）ツールです。C11 で実装されており、外部ライブラリ不要のポータブルなプログラムです。

> 🌐 他の言語でも読めます: [English](README.md) | [中文](README_zh.md)

---

## 機能一覧

| 機能 | 詳細 |
|---|---|
| 家庭用料金計算 | 5段階累進制の上水道料金；消費税（VAT）免除 |
| 商業用料金計算 | 定額の上水道料金 ＋ 20% VAT |
| 共通費用 | 排水料、雨水排水料、基本料金（日額） |
| 四半期統計 | 売上、費用、利益、法人税25%、最高・平均家庭用請求額 |
| 入力検証 | 負の使用量・無効な顧客種別を拒否 |
| 移植性 | C11準拠、外部実行時依存なし |

## クイックスタート

### 前提条件

| プラットフォーム | ツールチェーン |
|---|---|
| Linux / macOS | `gcc` または `clang`、`make` |
| Windows | [MSYS2](https://www.msys2.org/) に `mingw-w64-x86_64-gcc` と `make` |

### ビルド

```bash
make            # build/water_bill を生成
```

### 実行

```bash
./build/water_bill
```

実行例：

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

### テスト実行

```bash
make test       # テストスイート全体をビルドして実行
```

期待される出力：

```
Results: 87 passed / 0 failed / 87 total
```

## 料金体系

### 家庭用

| 使用量（m³/四半期） | 単価（GBP/m³） |
|---|---|
| 0 〜 5 | 0.20 |
| 6 〜 12 | 0.35 |
| 13 〜 25 | 0.50 |
| 26 〜 40 | 0.75 |
| 40 超 | 2.50 |

その他の四半期固定料金：

- **排水料金**：使用量の 95% × £0.25/m³
- **雨水排水料**：£10.00/四半期
- **基本料金**：£0.10/日 × 91日 ＝ £9.10
- **VAT**：0%（家庭用は非課税）

### 商業用

- **上水道料金**：£2.50/m³（定額）
- **排水料金**：使用量の 95% × £2.00/m³
- **雨水排水料**：£50.00/四半期
- **基本料金**：£1.30/日 × 91日 ＝ £118.30
- **VAT**：総料金の 20%

## プロジェクト構成

```
water-bill-calculator/
├── src/
│   ├── billing.h        # 料金定数、Bill 構造体、API
│   ├── billing.c        # 料金計算実装
│   ├── statistics.h     # Statistics 構造体、API
│   ├── statistics.c     # 四半期統計集計
│   └── main.c           # 対話型 CLI エントリポイント
├── tests/
│   ├── test_framework.h # ゼロ依存のテストマクロ
│   └── test_all.c       # テストスイート（87アサーション）
├── .github/
│   └── workflows/
│       ├── ci.yml       # Linux・macOS・Windows でビルド＆テスト
│       └── release.yml  # タグプッシュ時に GitHub Release を作成
├── Makefile
├── README.md            # English
├── README_zh.md         # 简体中文
├── README_ja.md         # このファイル（日本語）
├── LICENSE              # MIT ライセンス
├── CHANGELOG.md
└── CONTRIBUTING.md
```

## コントリビューション

コントリビューションを歓迎します！まず [CONTRIBUTING.md](CONTRIBUTING.md) をお読みください。

## ライセンス

このプロジェクトは **MIT ライセンス** の下で公開されています。詳細は [LICENSE](LICENSE) を参照してください。
