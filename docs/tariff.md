# Tariff Reference

This document describes the tariff structure used by the calculator.
All monetary values are in **GBP (£)**. Charges are applied per quarter
(91 days).

---

## Domestic Customers

Domestic customers are **VAT-exempt**.

### Fresh Water — 5-Tier Progressive Tariff

| Tier | Consumption (m³)  | Rate (GBP / m³) |
|------|-------------------|-----------------|
| 1    | 0 – 5             | £0.20           |
| 2    | 6 – 12            | £0.35           |
| 3    | 13 – 25           | £0.50           |
| 4    | 26 – 40           | £0.75           |
| 5    | > 40              | £2.50           |

Each tier rate applies only to the portion of consumption within that
band; lower-tier rates are not retroactively replaced.

### Fixed Charges (per quarter)

| Charge          | Rate                                              |
|-----------------|---------------------------------------------------|
| Waste water     | £0.25 / m³ applied to 95 % of consumption        |
| Surface water   | £10.00 flat                                       |
| Standing charge | £0.10 / day × 91 days = **£9.10**                |

---

## Commercial Customers

Commercial customers pay **20 % VAT** on the total charge (before VAT).

### Fresh Water — Flat Rate

| Charge          | Rate                                              |
|-----------------|---------------------------------------------------|
| Fresh water     | £2.50 / m³                                       |
| Waste water     | £2.00 / m³ applied to 95 % of consumption        |
| Surface water   | £50.00 flat                                       |
| Standing charge | £1.30 / day × 91 days = **£118.30**              |

---

## Utility Financials

| Item              | Rate                                              |
|-------------------|---------------------------------------------------|
| Operational cost  | £1.00 / m³ supplied (all customer types)          |
| Corporate tax     | 25 % of profit (only applied when profit > 0)     |

---

## Worked Examples

### Domestic — 20 m³

```
Tier 1:  5 × £0.20  =   £1.00
Tier 2:  7 × £0.35  =   £2.45
Tier 3:  8 × £0.50  =   £4.00
Fresh water total       £7.45

Waste:  20 × 0.95 × £0.25 = £4.75
Surface:                    £10.00
Standing:                    £9.10
──────────────────────────────────
Total (Amount to Pay)       £31.30
```

### Commercial — 100 m³

```
Fresh:   100 × £2.50          = £250.00
Waste:   100 × 0.95 × £2.00   = £190.00
Surface:                         £50.00
Standing:                       £118.30
                               ────────
Sub-total                      £608.30
VAT (20 %):                    £121.66
──────────────────────────────────────
Amount to Pay                  £729.96
```
