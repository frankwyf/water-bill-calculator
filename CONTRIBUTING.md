# Contributing Guide

Thank you for considering a contribution to **Water Bill Calculator**!

---

## Ways to contribute

- **Bug reports** — open an [Issue](../../issues) with a clear title, steps to reproduce, and expected vs actual behaviour
- **Feature requests** — open an Issue labelled `enhancement` and describe the use case
- **Pull requests** — fix a bug, improve tests, or add documentation

---

## Development workflow

### 1. Fork & clone

```bash
git clone https://github.com/<your-username>/water-bill-calculator.git
cd water-bill-calculator
```

### 2. Create a feature branch

```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/short-description
```

### 3. Make changes

- Keep changes focused — one concern per pull request.
- Follow the existing code style (see below).

### 4. Build and test

```bash
make
make test
```

All 87 tests must pass before submitting. Add new tests for any new functionality.

### 5. Commit

Use [Conventional Commits](https://www.conventionalcommits.org/):

```
feat: add CSV export for quarterly statistics
fix: correct tier-4 boundary calculation for domestic customers
docs: update Japanese README with new tariff table
test: add edge-case assertions for zero consumption
```

### 6. Push and open a Pull Request

```bash
git push origin feature/your-feature-name
```

Open a PR against `main`. The CI pipeline will run automatically.

---

## Coding style

| Rule | Detail |
|---|---|
| Standard | C11 (`-std=c11`) |
| Warnings | Code must compile cleanly with `-Wall -Wextra -Wpedantic` |
| Naming | `snake_case` for functions and variables; `UPPER_CASE` for macros and constants |
| Indentation | 4 spaces, no tabs |
| Line length | ≤ 100 characters |
| Comments | Use `/** … */` for public API documentation |

---

## Reporting security issues

Please **do not** open a public issue for security vulnerabilities.  
Send a private report via [GitHub Security Advisories](../../security/advisories).

---

## Code of Conduct

This project follows the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md).  
By participating, you agree to uphold these standards.
