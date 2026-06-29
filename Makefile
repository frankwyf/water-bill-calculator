# ==============================================================
# Makefile — Water Bill Calculator
#
# Common targets:
#   make              Build the main executable (default)
#   make test         Build and run the full test suite
#   make debug        Build with AddressSanitizer + UBSan
#   make install      Install to $(PREFIX)/bin  (default: /usr/local)
#   make uninstall    Remove installed binary
#   make clean        Remove build artefacts
#   make help         Print this message
#
# Variables you can override on the command line:
#   CC=clang          Compiler (default: gcc)
#   PREFIX=/opt       Install prefix (default: /usr/local)
#   DESTDIR=          Stage root for package builders
# ==============================================================

CC      ?= gcc
CFLAGS   = -Wall -Wextra -Wpedantic -std=c11

PREFIX  ?= /usr/local
BINDIR  ?= $(DESTDIR)$(PREFIX)/bin

SRCDIR    = src
TESTDIR   = tests
BUILDDIR  = build

SRCS        = $(SRCDIR)/billing.c $(SRCDIR)/statistics.c
TARGET      = $(BUILDDIR)/water_bill
TEST_TARGET = $(BUILDDIR)/test_runner

.PHONY: all test debug format install uninstall clean help

# ── Default ────────────────────────────────────────────────────────────────
all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(SRCDIR)/main.c $(SRCS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^

# ── Tests ──────────────────────────────────────────────────────────────────
$(TEST_TARGET): $(TESTDIR)/test_all.c $(SRCS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -o $@ $^ -lm

test: $(TEST_TARGET)
	$(TEST_TARGET)

# ── Debug / sanitizers ─────────────────────────────────────────────────────
# Builds the executable with AddressSanitizer and UBSan enabled.
# Requires gcc >= 4.8 or clang >= 3.1.
debug: CFLAGS += -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
debug: all

# ── Format (requires clang-format) ────────────────────────────────────────
format:
	clang-format -i $(SRCDIR)/*.c $(SRCDIR)/*.h $(TESTDIR)/*.c $(TESTDIR)/*.h

# ── Install / uninstall ────────────────────────────────────────────────────
install: $(TARGET)
	install -d $(BINDIR)
	install -m 0755 $(TARGET) $(BINDIR)/water_bill

uninstall:
	rm -f $(BINDIR)/water_bill

# ── Cleanup ────────────────────────────────────────────────────────────────
clean:
	rm -rf $(BUILDDIR)

# ── Help ───────────────────────────────────────────────────────────────────
help:
	@echo ""
	@echo "Water Bill Calculator — build targets"
	@echo ""
	@echo "  make              Build ./$(TARGET)"
	@echo "  make test         Build and run the test suite"
	@echo "  make debug        Build with AddressSanitizer + UBSan"
	@echo "  make format       Run clang-format on all source files"
	@echo "  make install      Install to \$$PREFIX/bin (default: /usr/local)"
	@echo "  make uninstall    Remove installed binary"
	@echo "  make clean        Remove $(BUILDDIR)/"
	@echo ""
	@echo "Override variables:"
	@echo "  CC=clang          Use clang instead of gcc"
	@echo "  PREFIX=/opt       Change install prefix"
	@echo "  DESTDIR=/staging  Stage root for package builds"
	@echo ""
