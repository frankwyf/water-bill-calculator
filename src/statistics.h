/**
 * @file statistics.h
 * @brief Quarterly statistics aggregation interface
 */
#ifndef STATISTICS_H
#define STATISTICS_H

#include "billing.h"

/**
 * @brief Aggregated quarterly statistics for the water utility.
 */
typedef struct {
    double total_fresh_water;     /**< Total m³ supplied to all customers */
    double total_domestic_water;  /**< Total m³ supplied to domestic customers */
    double revenue;               /**< Total revenue (excl. VAT) from all customers */
    double cost;                  /**< Operational cost (WATER_COST_PER_M3 × total m³) */
    double profit;                /**< revenue − cost */
    double income_tax;            /**< 25 % of profit (zero if profit ≤ 0) */
    double max_domestic_bill;     /**< Highest domestic bill seen this quarter */
    double avg_domestic_bill;     /**< Mean domestic bill this quarter */
    int    domestic_count;        /**< Number of domestic customers billed */
    double domestic_revenue;      /**< Revenue from domestic customers only */
} Statistics;

/** @brief Initialise all fields to zero. */
void stats_init(Statistics *s);

/** @brief Update aggregate statistics after a bill is computed. */
void stats_update(Statistics *s, const Bill *bill);

/** @brief Print formatted summary statistics to stdout. */
void stats_display(const Statistics *s);

#endif /* STATISTICS_H */
