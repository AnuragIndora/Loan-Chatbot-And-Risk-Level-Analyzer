# Loan Chatbot & Risk Level Analyzer

Welcome to the **Loan Chatbot**, a command-line tool designed to assist users in understanding loan-related topics and calculating loan risk levels. It offers both an interactive chatbot and batch processing features for real-world financial analysis.

---

## Features

### 1. Loan Question & Answer Chatbot

You can ask the chatbot questions such as:

* `What is EMI?`
* `How to apply for a loan?`
* `Explain interest rate`
* `What is foreclosure?`

The chatbot provides:

* Intelligent understanding of synonyms (e.g., “monthly payment” is interpreted as “EMI”)
* Suggestions for similar questions if an exact match is not found
* The ability to add custom questions and answers to its knowledge base
* Logging of all user queries to `chatlog.txt`

---

### 2. Manual Loan Risk Calculation

Select the option `calculate risk` to manually input:

* Missed repayments
* Loan amount
* Collateral value
* Interest rate

The chatbot will compute a **risk score** using the following formula:

```
risk_score = (missed_repayments * 2) + (loan_amount / collateral_value) + (interest / 2)
```

It will then classify the risk according to the score:

| Risk Score Range | Risk Level |
| ---------------- | ---------- |
| 0–15             | LOW        |
| 15–25            | MEDIUM     |
| 25+              | HIGH       |

---

### 3. Batch Risk Calculation (CSV File)

Select `csv risk` to:

* Load loan records from `loan_data.csv`
* Automatically compute the risk score and classification for each entry
* Generate a new file `output_with_risk.csv` containing additional `risk_score` and `risk_level` columns

---

### Important Note: CSV Format Requirement

For the batch risk calculation to function correctly, the input file `loan_data.csv` must strictly follow a specific **column order**. Although column headers can be named freely, the **position and meaning of data in each row must remain consistent** as follows:

| Column Position | Expected Data Type | Description                              | Example Header Name                     |
| --------------- | ------------------ | ---------------------------------------- | --------------------------------------- |
| 1               | String             | Loan account number or unique identifier | `loan_acc_num`, `loan_id`, `account_no` |
| 2               | Integer            | Number of missed repayments              | `missed_repayments`, `no_missed`        |
| 3               | Decimal / Numeric  | Loan amount                              | `loan_amount`, `loan_amount_value`      |
| 4               | Decimal / Numeric  | Collateral value                         | `collateral_value`, `collateral_money`  |
| 5               | Decimal / Numeric  | Interest rate (%)                        | `interest`, `interest_rate`             |

#### Guidelines:

* Column **headers** can be custom-named, but the **position and data type of each column must follow the order above**.
* The system reads data based on position only; it does not rely on header names.
* Incorrect column order or mismatched data types (e.g., text in numeric fields) may result in processing errors or incorrect risk evaluations.

> Tip: Always validate that each row matches the expected order and types before running batch analysis.

---

## How to Use the Application

### Step 1: Ensure `make` is Installed

* On **Linux/macOS**: `make` is typically pre-installed.
* On **Windows**: Install `make` via Git Bash, WSL, or a MinGW environment.

### Step 2: Open a Terminal in the Project Directory

### Step 3: Build the Application

```bash
make
```

### Step 4: Run the Application

```bash
make run
```

### Step 5: Clean Build Files (Optional)

```bash
make clean
```

---

## Project Files

| File Name              | Description                                                   |
| ---------------------- | ------------------------------------------------------------- |
| `main.cpp`             | Main C++ source file containing the chatbot and logic         |
| `Makefile`             | Build script for compiling, running, and cleaning the project |
| `LoanFAQs.txt`         | Plain-text file containing chatbot questions and answers      |
| `loan_data.csv`        | Sample CSV file for batch risk input                          |
| `output_with_risk.csv` | Output file with computed risk scores and classifications     |
| `chatlog.txt`          | Log file recording all user questions                         |
| `README.md`            | Documentation file (this one)                                 |

---

## How to Add Custom Questions

1. Run the chatbot using:

   ```bash
   make run
   ```
2. Type `add` at the prompt
3. Enter a new question and its corresponding answer
4. The new entry is saved to `LoanFAQs.txt` and persists across sessions

---

## Chatbot Intelligence Features

The chatbot system includes the following capabilities:

* Input normalization (trimming, case standardization, and spacing)
* Synonym detection and substitution (e.g., “installment” → “EMI”)
* Suggestive search when no exact match is found
* Customizable knowledge base through user interaction
* Real-time CSV parsing for batch loan risk classification

---

## Common Commands

| Command          | Action                                                   |
| ---------------- | -------------------------------------------------------- |
| `<Question>`     | Retrieves the answer from the knowledge base             |
| `add`            | Allows the user to input a new question and answer       |
| `calculate risk` | Prompts the user for input and returns a risk evaluation |
| `csv risk`       | Processes records from a CSV and generates output        |
| `exit`           | Closes the chatbot session                               |

---

