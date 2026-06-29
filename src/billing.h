/**
 * @file billing.h
 * @brief Water bill calculation interface
 *
 * Defines pricing constants, data structures, and function declarations
 * for computing quarterly water bills for domestic and commercial customers.
 */
#ifndef BILLING_H
#define BILLING_H

/* ── Quarterly period ─────────────────────────────────────────────────────── */
#define DAYS_PER_QUARTER 91

/* ── Domestic fresh-water tiered pricing (GBP per m³) ────────────────────── */
#define DOM_TIER1_RATE   0.20
#define DOM_TIER1_MAX    5
#define DOM_TIER2_RATE   0.35
#define DOM_TIER2_MAX    12
#define DOM_TIER3_RATE   0.50
#define DOM_TIER3_MAX    25
#define DOM_TIER4_RATE   0.75
#define DOM_TIER4_MAX    40
#define DOM_TIER5_RATE   2.50

/* ── Waste water billing fraction ────────────────────────────────────────── */
#define WASTE_WATER_FRACTION   0.95   /**< Fraction of consumption billed as waste water */

/* ── Domestic fixed charges ───────────────────────────────────────────────── */
#define DOM_WASTE_RATE         0.25   /**< GBP per m³ (applied to WASTE_WATER_FRACTION of consumption) */
#define DOM_SURFACE_CHARGE    10.00   /**< GBP per quarter */
#define DOM_STANDING_RATE      0.10   /**< GBP per day */
#define DOM_VAT_RATE           0.00   /**< Domestic customers are VAT-exempt */

/* ── Commercial pricing ───────────────────────────────────────────────────── */
#define COM_FRESH_RATE         2.50   /**< GBP per m³ */
#define COM_WASTE_RATE         2.00   /**< GBP per m³ (applied to WASTE_WATER_FRACTION of consumption) */
#define COM_SURFACE_CHARGE    50.00   /**< GBP per quarter */
#define COM_STANDING_RATE      1.30   /**< GBP per day */
#define COM_VAT_RATE           0.20   /**< 20 % VAT */

/* ── Business financials ──────────────────────────────────────────────────── */
#define WATER_COST_PER_M3      1.00   /**< Operational cost GBP per m³ supplied */
#define INCOME_TAX_RATE        0.25   /**< 25 % corporate income tax on profit */

/* ── Customer type ────────────────────────────────────────────────────────── */
typedef enum {
    CUSTOMER_DOMESTIC   = 1,
    CUSTOMER_COMMERCIAL = 2
} CustomerType;

/* ── Computed bill for one customer ──────────────────────────────────────── */
typedef struct {
    CustomerType type;
    int          consumption;           /**< m³ consumed this quarter */
    double       fresh_water_charge;    /**< GBP */
    double       waste_water_charge;    /**< GBP */
    double       surface_water_charge;  /**< GBP */
    double       standing_charge;       /**< GBP */
    double       total_charge;          /**< sum of all charges before VAT */
    double       vat;                   /**< VAT amount */
    double       amount_to_pay;         /**< total_charge + vat */
} Bill;

/**
 * @brief Compute a quarterly water bill.
 *
 * @param type        Customer type (CUSTOMER_DOMESTIC or CUSTOMER_COMMERCIAL).
 * @param consumption Water consumption in m³ (must be >= 0).
 * @param out         Pointer to a Bill struct to fill; must not be NULL.
 * @return            0 on success, -1 if consumption < 0 or out is NULL.
 */
int compute_bill(CustomerType type, int consumption, Bill *out);

/**
 * @brief Print a formatted bill to stdout.
 * @param bill  Pointer to a computed Bill; must not be NULL.
 */
void print_bill(const Bill *bill);

#endif /* BILLING_H */
