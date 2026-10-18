# Password Export Parser

A small, **fully local** C++ console tool that reads a browser/password-manager
CSV export and converts it into a file format of your choice — **HTML**
(opens in both Word and Excel), **CSV**, or plain **TXT**.

It is meant for one thing only: helping you take **your own** exported
credentials and save them locally in a readable format. The application has
**no network access** and sends nothing anywhere — everything happens on your
machine.

---

## ⚠️ Security notice — read this first

- This tool writes your passwords into a **plaintext** file (HTML/CSV/TXT).
  Anyone with access to that file can read them. Store the output somewhere safe
  (e.g. an encrypted drive) and delete it when you no longer need it.
- **Never commit a real export to Git.** The included [`.gitignore`](.gitignore)
  already blocks `*.csv` and `lozinke.*` so your real passwords don't end up on
  GitHub by accident. Double-check before pushing.
- A dedicated, audited password manager is still the safer place to keep
  credentials. This tool is a convenience converter, not a storage solution.

---

## Supported input

The CSV is parsed by a proper RFC‑4180‑style state machine, so **any**
well-formed CSV is read correctly (quoted fields, commas and newlines inside
quotes, escaped `""`, and a UTF‑8 BOM are all handled).

Columns are mapped **by header name**, not by position, so the column order
does not matter. The `ColumnMapper` recognises common header names and their
aliases for each field:

| Field | Recognised headers (case-insensitive) |
|-------|----------------------------------------|
| name | `name`, `title`, `item`, `account` |
| url | `url`, `uri`, `website`, `login_uri`, `login_url`, `site` |
| username | `username`, `user`, `login_username`, `email`, `e-mail` |
| password | `password`, `pass`, `pwd`, `login_password` |
| note | `note`, `notes`, `extra`, `comment`, `comments` |

This makes the tool work out of the box with exports from **Comet, Chrome,
Edge, Brave, 1Password, Bitwarden, LastPass, Firefox**, and similar.

Unrecognised columns are simply ignored, and any field not present stays empty.
If no known header is found at all, the parser falls back to the Chromium
positional layout `name,url,username,password,note`.

To support another manager, just add its header spelling to the alias lists in
`ColumnMapper.cpp` — no other class changes.

---

## Build

Requires **Visual Studio 2022+** with the C++ workload (project targets C++20).

1. Open `ParsePasswordsFromComet.slnx` in Visual Studio.
2. Select a configuration (e.g. `Debug | x64`).
3. **Build → Rebuild Solution**.

The parser is also standard C++ and builds with any C++17 compiler, e.g.:

```sh
g++ -std=c++17 -Wall -Wextra -o parser \
    main.cpp FileReader.cpp CsvParser.cpp ColumnMapper.cpp \
    TxtExporter.cpp CsvExporter.cpp HtmlExporter.cpp \
    ExporterFactory.cpp Application.cpp
```

---

## Usage

Place your export (default name `Comet Passwords.csv`) next to the executable,
then run it:

```
=== Parser lozinki (lokalno, bez mreze) ===

Putanja do CSV datoteke [Comet Passwords.csv]: <Enter for default, or type a path>
Ucitano valjanih zapisa: 72

Odaberi format izlaza:
  1) HTML  (opens in Word and Excel)
  2) CSV   (opens in Excel)
  3) TXT   (plain text)
Izbor: 1

Spremljeno: lozinke.html
```

The output file (`lozinke.html` / `lozinke.csv` / `lozinke.txt`) is written to
the current directory.

---

## Project structure

Each class has a single responsibility (SRP); the formats use polymorphism
behind the `IExporter` interface.

| File | Responsibility |
|------|----------------|
| `PasswordRecord.h` | Data model for one entry + `isValid()` keep/skip rule |
| `FileReader` | Read a file into a string |
| `CsvParser` | Turn raw CSV text into records (quote-aware state machine) |
| `ColumnMapper` | Map columns to fields by header name (cross-manager support) |
| `IExporter` | Abstract interface every exporter implements |
| `HtmlExporter` / `CsvExporter` / `TxtExporter` | Write one specific format |
| `ExporterFactory` | Pick the exporter for the chosen format |
| `Application` | Orchestrates the flow; `try/catch` keeps it from crashing |
| `main.cpp` | Entry point — just starts `Application` |

Adding a new output format = add an `OutputFormat` member, a new
`IExporter` subclass, and one branch in `ExporterFactory`. No existing class
changes (Open/Closed principle).

---

## Roadmap

- Optional password masking in the output (`••••`).
- Real `.xlsx` / `.docx` output (requires a third-party library).

---

## License

Add a license of your choice (e.g. MIT) before publishing.
