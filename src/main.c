/**
 * @file main.c
 * @brief Water Bill Calculator — interactive CLI entry point
 *
 * A quarterly water billing calculator for domestic and commercial
 * customers of a hypothetical water utility using a UK-style tariff structure.
 *
 * Usage: water_bill
 */
#include <stdio.h>
#include <stdlib.h>
#include "billing.h"
#include "statistics.h"

static void flush_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void print_menu(void)
{
    printf("\n===========================================\n");
    printf("         Water Bill Calculator\n");
    printf("===========================================\n");
    printf("  1. Compute and display a customer bill\n");
    printf("  2. Display quarterly statistics\n");
    printf("  3. Quit\n");
    printf("===========================================\n");
}

int main(void)
{
    Statistics stats;
    stats_init(&stats);

    print_menu();

    int choice;
    while (1) {
        printf("\nEnter your choice (1-3): ");
        if (scanf("%d", &choice) != 1) {
            flush_stdin();
            printf("Invalid input. Please enter 1, 2, or 3.\n");
            continue;
        }

        switch (choice) {
        case 1: {
            int ctype;
            printf("Customer type  (1=Domestic, 2=Commercial): ");
            if (scanf("%d", &ctype) != 1 ||
                (ctype != CUSTOMER_DOMESTIC && ctype != CUSTOMER_COMMERCIAL)) {
                flush_stdin();
                printf("Invalid customer type. Please enter 1 or 2.\n");
                break;
            }

            int consumption;
            printf("Water consumption (m3): ");
            if (scanf("%d", &consumption) != 1 || consumption < 0) {
                flush_stdin();
                printf("Invalid consumption. Must be a non-negative integer.\n");
                break;
            }

            Bill bill;
            if (compute_bill((CustomerType)ctype, consumption, &bill) != 0) {
                printf("Failed to compute bill.\n");
                break;
            }

            print_bill(&bill);
            stats_update(&stats, &bill);
            break;
        }

        case 2:
            stats_display(&stats);
            break;

        case 3:
            printf("Goodbye.\n");
            return EXIT_SUCCESS;

        default:
            printf("Please enter 1, 2, or 3.\n");
        }
    }
}
