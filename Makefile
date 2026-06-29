# ==============================================================
# Makefile — Water Bill Calculator
# Targets: all, test, clean
# Usage:
#   make            → build the main executable
#   make test       → build and run all tests
#   make clean      → remove build artefacts
# Override compiler: make CC=clang
# ==============================================================

CC      ?= gcc
CFLAGS   = -Wall -Wextra -Wpedantic -std=c11

SRCDIR   = src
TESTDIR  = tests
BINDIR   = build

SRCS        = $(SRCDIR)/billing.c $(SRCDIR)/statistics.c
TARGET      = $(BINDIR)/water_bill
TEST_TARGET = $(BINDIR)/test_runner

.PHONY: all test clean

all: $(BINDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(SRCDIR)/main.c $(SRCS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TESTDIR)/test_all.c $(SRCS) | $(BINDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -o $@ $^ -lm

test: $(TEST_TARGET)
	$(TEST_TARGET)

clean:
	rm -rf $(BINDIR)
