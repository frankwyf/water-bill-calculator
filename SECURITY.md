# Security Policy

## Supported Versions

| Version | Supported          |
|---------|--------------------|
| 1.x     | :white_check_mark: |

## Reporting a Vulnerability

If you discover a security vulnerability in this project, please report it
**responsibly** — do **not** open a public GitHub issue.

### How to report

1. Go to the [Security Advisories](../../security/advisories) page.
2. Click **"Report a vulnerability"**.
3. Provide a clear description, steps to reproduce, and impact assessment.

We will acknowledge your report within **72 hours** and aim to provide a
fix or mitigation within **14 days**, depending on severity.

### What qualifies

- Buffer overflows or memory corruption in the billing engine
- Integer overflow in charge computation
- Input handling that could cause undefined behaviour
- Denial-of-service via crafted input (e.g. extremely large consumption values)

### Out of scope

- Issues that require physical access to the machine
- Social engineering
- Bugs in third-party dependencies not bundled with this project

## Disclosure

We follow [coordinated disclosure](https://en.wikipedia.org/wiki/Coordinated_vulnerability_disclosure).
Credit will be given to reporters in the release notes unless they prefer
to remain anonymous.
