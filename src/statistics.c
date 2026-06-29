/**
 * @file statistics.c
 * @brief Quarterly statistics aggregation implementation
 */
#include <stdio.h>
#include <string.h>
#include "statistics.h"

void stats_init(Statistics *s)
{
    if (s == NULL) return;
    memset(s, 0, sizeof(*s));
}

void stats_update(Statistics *s, const Bill *bill)
{
    if (s == NULL || bill == NULL) return;

    s->total_fresh_water += bill->consumption;

    if (bill->type == CUSTOMER_DOMESTIC) {
        s->total_domestic_water += bill->consumption;
        s->domestic_revenue     += bill->total_charge;
        s->domestic_count++;
        if (bill->total_charge > s->max_domestic_bill)
            s->max_domestic_bill = bill->total_charge;
        s->avg_domestic_bill = s->domestic_revenue / s->domestic_count;
    }

    s->revenue   += bill->total_charge;
    s->cost       = s->total_fresh_water * WATER_COST_PER_M3;
    s->profit     = s->revenue - s->cost;
    s->income_tax = (s->profit > 0.0) ? s->profit * INCOME_TAX_RATE : 0.0;
}

void stats_display(const Statistics *s)
{
    if (s == NULL) return;
    printf("Total Fresh Water Supplied:              %.2f m3\n",  s->total_fresh_water);
    printf("Total Fresh Water to Domestic Customers: %.2f m3\n",  s->total_domestic_water);
    printf("Total Revenue:                           %.2f GBP\n", s->revenue);
    printf("Total Cost:                              %.2f GBP\n", s->cost);
    if (s->profit >= 0.0)
        printf("Profit:                                  %.2f GBP\n",  s->profit);
    else
        printf("Loss:                                    %.2f GBP\n", -s->profit);
    printf("Income Tax:                              %.2f GBP\n", s->income_tax);
    printf("Maximum Domestic Bill:                   %.2f GBP\n", s->max_domestic_bill);
    printf("Average Domestic Bill:                   %.2f GBP\n", s->avg_domestic_bill);
}
