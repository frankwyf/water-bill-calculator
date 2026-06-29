/**
 * @file billing.c
 * @brief Water bill computation implementation
 */
#include <stdio.h>
#include "billing.h"

/* Compute fresh-water charge for domestic customers using tiered pricing */
static double domestic_fresh_water_charge(int consumption)
{
    double charge = 0.0;
    int    c      = consumption;

    if (c <= 0) return 0.0;

    /* Tier 1: 0–5 m³ */
    int tier1 = DOM_TIER1_MAX;
    if (c <= tier1) { charge += c * DOM_TIER1_RATE; return charge; }
    charge += tier1 * DOM_TIER1_RATE;
    c      -= tier1;

    /* Tier 2: 6–12 m³ */
    int tier2 = DOM_TIER2_MAX - DOM_TIER1_MAX;
    if (c <= tier2) { charge += c * DOM_TIER2_RATE; return charge; }
    charge += tier2 * DOM_TIER2_RATE;
    c      -= tier2;

    /* Tier 3: 13–25 m³ */
    int tier3 = DOM_TIER3_MAX - DOM_TIER2_MAX;
    if (c <= tier3) { charge += c * DOM_TIER3_RATE; return charge; }
    charge += tier3 * DOM_TIER3_RATE;
    c      -= tier3;

    /* Tier 4: 26–40 m³ */
    int tier4 = DOM_TIER4_MAX - DOM_TIER3_MAX;
    if (c <= tier4) { charge += c * DOM_TIER4_RATE; return charge; }
    charge += tier4 * DOM_TIER4_RATE;
    c      -= tier4;

    /* Tier 5: > 40 m³ */
    charge += c * DOM_TIER5_RATE;
    return charge;
}

int compute_bill(CustomerType type, int consumption, Bill *out)
{
    if (out == NULL || consumption < 0) return -1;

    out->type        = type;
    out->consumption = consumption;

    switch (type) {
    case CUSTOMER_DOMESTIC:
        out->fresh_water_charge   = domestic_fresh_water_charge(consumption);
        out->waste_water_charge   = consumption * 0.95 * DOM_WASTE_RATE;
        out->surface_water_charge = DOM_SURFACE_CHARGE;
        out->standing_charge      = DOM_STANDING_RATE * DAYS_PER_QUARTER;
        out->total_charge         = out->fresh_water_charge
                                  + out->waste_water_charge
                                  + out->surface_water_charge
                                  + out->standing_charge;
        out->vat           = 0.0;
        out->amount_to_pay = out->total_charge;
        break;

    case CUSTOMER_COMMERCIAL:
        out->fresh_water_charge   = consumption * COM_FRESH_RATE;
        out->waste_water_charge   = consumption * 0.95 * COM_WASTE_RATE;
        out->surface_water_charge = COM_SURFACE_CHARGE;
        out->standing_charge      = COM_STANDING_RATE * DAYS_PER_QUARTER;
        out->total_charge         = out->fresh_water_charge
                                  + out->waste_water_charge
                                  + out->surface_water_charge
                                  + out->standing_charge;
        out->vat           = out->total_charge * COM_VAT_RATE;
        out->amount_to_pay = out->total_charge + out->vat;
        break;

    default:
        return -1;
    }

    return 0;
}

void print_bill(const Bill *bill)
{
    if (bill == NULL) return;
    printf("------------------------------------------\n");
    printf("Customer Type:        %s\n",
           bill->type == CUSTOMER_DOMESTIC ? "Domestic" : "Commercial");
    printf("Water Consumption:    %d m3\n",  bill->consumption);
    printf("Fresh Water Charge:   %.2f GBP\n", bill->fresh_water_charge);
    printf("Waste Water Charge:   %.2f GBP\n", bill->waste_water_charge);
    printf("Surface Water Charge: %.2f GBP\n", bill->surface_water_charge);
    printf("Standing Charge:      %.2f GBP\n", bill->standing_charge);
    printf("Total Charge:         %.2f GBP\n", bill->total_charge);
    printf("VAT:                  %.2f GBP\n", bill->vat);
    printf("Amount to Pay:        %.2f GBP\n", bill->amount_to_pay);
    printf("------------------------------------------\n");
}
