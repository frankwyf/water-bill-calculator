/**
 * @file main.c
 * @brief Water Bill Calculator — interactive and batch CLI entry point
 *
 * A quarterly water billing calculator for domestic and commercial
 * customers of a hypothetical water utility using a UK-style tariff structure.
 *
 * Usage:
 *   water_bill                  Interactive mode (menu-driven)
 *   water_bill --batch          Non-interactive: read <type> <m3> pairs from stdin
 *   water_bill --version        Print version and exit
 *   water_bill --help           Print help and exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"
#include "statistics.h"
#include "version.h"

static void flush_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void print_usage(void)
{
    printf("Usage: %s [OPTION]\n\n", WBC_PROGNAME);
    printf("Options:\n");
    printf("  --batch     Non-interactive mode: read <type> <m3> pairs from stdin,\n");
    printf("              one per line (1=Domestic, 2=Commercial). Lines starting\n");
    printf("              with '#' and blank lines are ignored. Prints all bills\n");
    printf("              and a statistics summary, then exits.\n");
    printf("  --version   Print version information and exit.\n");
    printf("  --help      Print this help message and exit.\n");
    printf("\nExamples:\n");
    printf("  %s\n", WBC_PROGNAME);
    printf("  echo '1 20' | %s --batch\n", WBC_PROGNAME);
    printf("  printf '1 12\\n2 100\\n1 40' | %s --batch\n", WBC_PROGNAME);
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

/* Run the batch mode: read (type, consumption) pairs from stdin. */
static int run_batch(void)
{
    Statistics stats;
    stats_init(&stats);

    int ctype, consumption;
    int line = 0;
    int records = 0;
    int errors = 0;
    char buf[256];

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        line++;
        /* Skip blank lines and comments */
        const char *p = buf;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\n' || *p == '\0' || *p == '#')
            continue;

        if (sscanf(buf, "%d %d", &ctype, &consumption) != 2) {
            fprintf(stderr, "line %d: expected '<type> <m3>' pair\n", line);
            errors++;
            continue;
        }
        records++;

        if (ctype != CUSTOMER_DOMESTIC && ctype != CUSTOMER_COMMERCIAL) {
            fprintf(stderr, "line %d: invalid customer type %d (use 1 or 2)\n",
                    line, ctype);
            errors++;
            continue;
        }
        if (consumption < 0) {
            fprintf(stderr, "line %d: negative consumption %d\n",
                    line, consumption);
            errors++;
            continue;
        }

        Bill bill;
        if (compute_bill((CustomerType)ctype, consumption, &bill) != 0) {
            fprintf(stderr, "line %d: failed to compute bill\n", line);
            errors++;
            continue;
        }

        print_bill(&bill);
        stats_update(&stats, &bill);
    }

    if (records == 0) {
        fprintf(stderr, "%s --batch: no input records read from stdin\n",
                WBC_PROGNAME);
        return EXIT_FAILURE;
    }

    printf("\n");
    stats_display(&stats);
    return (errors > 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    /* ── Argument parsing ── */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage();
            return EXIT_SUCCESS;
        }
        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-V") == 0) {
            printf("%s %s\n", WBC_PROGNAME, WBC_VERSION);
            return EXIT_SUCCESS;
        }
        if (strcmp(argv[i], "--batch") == 0) {
            return run_batch();
        }
        fprintf(stderr, "%s: unknown option '%s'\n"
                        "Try '%s --help' for usage information.\n",
                WBC_PROGNAME, argv[i], WBC_PROGNAME);
        return EXIT_FAILURE;
    }

    /* ── Interactive mode ── */
    Statistics stats;
    stats_init(&stats);

    int choice;
    while (1) {
        print_menu();
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

