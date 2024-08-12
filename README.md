# Signal Probability Analysis Using Topological Sort

## Overview

This project focuses on computing the signal probabilities in digital circuits and analyzing the likelihood of logic 0 or 1 across output nodes to ensure circuit reliability. The project implements Topological Sorting in C to determine the correct node operation sequence and optimizes circuit design to minimize failure risks.

## Features

- **Probability Calculation:** Computes signal probabilities for various gates in digital circuits.
- **Topological Sorting:** Ensures correct node operation sequence using Topological Sorting.
- **Circuit Design Optimization:** Analyzes and improves signal propagation paths.
- **Robust Verification:** Provides accurate probability analysis for better circuit design and validation.

## Requirements

- **Programming Language:** C
- **Input Files:** Bench files such as `c17.bench`, `c432.bench`, `c499.bench`, `c880.bench`, `c1355.bench`
- **Output Files:** `result.txt`, `relationfile.txt`

## Setup and Execution

1. **Clone the Repository:**
   ```bash
   git clone <repository_url>
   cd <repository_directory>
2. **Prepare Input Files:**
   - Ensure the bench files (c17.bench, c432.bench, c499.bench, c880.bench, c1355.bench) are in the project directory.
3. **Compile the Code:**
   ```bash
   gcc -o signal_analysis signal_analysis.c
4. **Run the Program:**
   ```bash
   ./signal_analysis
5. **Check the results**
   - The output will be saved in result.txt.
   - Intermediate relations will be stored in relationfile.txt.
# Explanation
## Probability Calculation
- Computes the probability of logic 0 or 1 for each gate in the digital circuit.
- **Probability Functions:**
  - **AND:** `pOfAND(pi1, pi2)`
  - **NAND:** `pOfNAND(pi1, pi2)`
  - **NOT:** `pOfNOT(p1)`
  - **OR:** `pOfOR(pi1, pi2)`
  - **NOR:** `pOfNOR(pi1, pi2)`
  - **XOR:** `pOfXOR(pi1, pi2)`
  - **XNOR:** `pOfXNOR(pi1, pi2)`
  - **BUFF:** `pOfBUFF(p1)`

- **Topological Sorting:**
  - Implemented to determine the correct order of node operations.
  - Ensures that each node is processed only after its dependencies have been processed.

- **Circuit Design Optimization:**
  - Analyzes signal propagation paths to identify and minimize potential failure points.
  - Improves the reliability and robustness of the circuit design.

## Benefits

- **Enhanced Reliability:** Provides insights into the likelihood of different signal states, which helps in designing more reliable circuits.
- **Improved Design:** Optimizes signal propagation paths, reducing the risk of circuit failure.
- **Accurate Analysis:** Offers precise probability calculations for robust circuit verification.

## Outcome

The project successfully calculates signal probabilities, implements Topological Sorting, and optimizes digital circuit designs. The results assist in designing more reliable circuits and verifying their robustness.

## Contributing

Contributions are welcome. Please submit a pull request with your changes or enhancements.

    
