# 💬 Loan Chatbot & Risk Level Analyzer (OOP Version)

An intelligent **command-line chatbot** built with C++ and Object-Oriented Programming (OOP) principles. This assistant can answer loan-related questions, compute risk levels interactively, or process them in bulk using CSV files.

---

## 🔧 Features Overview

### ✅ 1. Smart Loan Chatbot

Ask questions like:

* `What is EMI?`
* `Define collateral`
* `How do I apply for a loan?`

**Key Functionalities:**

* ✅ Synonym-aware query matching (e.g., "monthly payment" → "EMI")
* ✅ Suggests close matches if an exact question isn't found
* ✅ Accepts new questions/answers to expand the knowledge base
* ✅ Logs all user inputs to `chatlog.txt` for future analysis

---

### 📉 2. Manual Loan Risk Calculator

Choose the option `calculate risk` and input:

* ❗ Number of missed payments
* 💰 Loan amount
* 🛡️ Collateral value
* 📈 Interest rate

The system uses this formula:

```
risk_score = (missed_repayments * 2) + (loan_amount / collateral_value) + (interest / 2)
```

| Risk Score | Level  |
| ---------- | ------ |
| 0–15       | LOW    |
| 15–25      | MEDIUM |
| 25+        | HIGH   |

---

### 📁 3. CSV-Based Bulk Risk Analyzer

Use the command `csv risk` to:

* 📂 Read loan data from a CSV file (e.g., `loan_data.csv`)
* ✅ Compute risk scores and levels automatically
* 📤 Output to `output_with_risk.csv` with additional risk columns

#### 🔍 Required CSV Column Order:

| Index | Field             | Example Header      |
| ----- | ----------------- | ------------------- |
| 1     | Loan ID (string)  | `loan_id`           |
| 2     | Missed payments   | `missed_repayments` |
| 3     | Loan amount       | `loan_amount`       |
| 4     | Collateral value  | `collateral_value`  |
| 5     | Interest rate (%) | `interest_rate`     |

> **⚠️ Note**: Headers can be custom-named, but **data order and types must match**.

---

## 🧠 Chatbot Intelligence

* 🧹 Input normalization: case-insensitive, whitespace trimming
* 🔁 Synonym replacement: e.g., "describe EMI" → "what is EMI"
* 🔍 Fuzzy matching for close questions
* 📝 Custom Q\&A support (saved to `LoanFAQs.txt`)

---

## 🧪 How to Use the Application

### 🔨 Build the Project

```bash
make
```

### 🚀 Run the Chatbot

```bash
make run
```

### 🧼 Clean Build Files

```bash
make clean
```

---

## 📂 Project Structure

| File/Folder             | Description                                         |
| ----------------------- | --------------------------------------------------- |
| `main.cpp`              | Entry point of the application                      |
| `Chatbot.hpp/.cpp`      | Chatbot class (user interaction logic)              |
| `FAQManager.hpp/.cpp`   | Handles FAQ storage, search, and editing            |
| `RiskAnalyzer.hpp/.cpp` | Risk scoring logic (manual & CSV modes)             |
| `Utils.hpp/.cpp`        | Helper functions (normalization, logging, synonyms) |
| `LoanFAQs.txt`          | Text file containing loan Q\&A                      |
| `loan_data.csv`         | Sample input file for batch risk evaluation         |
| `output_with_risk.csv`  | Output CSV with risk scores                         |
| `chatlog.txt`           | Log of all user-entered questions                   |
| `Makefile`              | Compilation, run, and clean commands                |
| `README.md`             | You're reading it!                                  |

---

## ➕ Adding New Questions

1. Run the app: `make run`
2. Type `add`
3. Enter your new question and answer
4. It's saved in `LoanFAQs.txt` and available instantly

---

## 💡 Supported Commands

| Command          | Description                                  |
| ---------------- | -------------------------------------------- |
| `<Any question>` | Fetch an answer from the knowledge base      |
| `add`            | Add a new Q\&A entry to the database         |
| `calculate risk` | Perform manual loan risk evaluation          |
| `csv risk`       | Perform bulk loan risk scoring via CSV input |
| `exit`           | Quit the chatbot                             |

---

## 👨‍💻 Technologies Used

* Language: C++ (Object-Oriented)
* Build Tool: `make`
* File I/O: Plaintext + CSV
* Synonym matching: `std::regex`, mapping logic
* Data storage: `unordered_map` for fast lookup

---

## 📌 Example Use Case

```bash
make run
```

```
> What is monthly payment?
  EMI stands for Equated Monthly Installment...

> calculate risk
  Missed payments: 2
  Loan amount: 50000
  Collateral: 20000
  Interest: 10
  Risk Level: LOW
```

---

## 🏁 Final Notes

* Make sure your input CSV follows the correct structure.
* Extend the chatbot easily by updating `LoanFAQs.txt`.
* Logs and risk reports are generated automatically.

---

**Built with ❤️ using Object-Oriented C++ for smarter financial interaction.**
Feel free to contribute or customize for your use case!
