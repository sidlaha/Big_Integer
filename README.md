# Large Number Arithmetic & FFT Tools

## Description
This repository contains C++ implementations for handling advanced arithmetic operations on large numbers[cite: 1, 2, 4, 6]. To handle numbers that exceed standard data type limits, the project represents numbers as strings and utilizes the Fast Fourier Transform (FFT) to optimize multiplication computations[cite: 1, 2, 6].

## Features
*   **Fast Exponentiation:** Features a `powerFFT` function that calculates a large base raised to an exponent using FFT-based multiplication[cite: 1].
*   **Large Factorials:** Computes the factorial of a user-provided integer by iteratively multiplying the sequence using FFT[cite: 2].
*   **Primality Testing:** Includes an `isPrime` function that checks if a large number is prime by squaring incrementally larger numbers using FFT and checking remainders[cite: 6].
*   **Standard String Multiplication:** Provides a foundational algorithm to multiply two large string-based numbers digit-by-digit[cite: 4].

## Requirements
*   A C++ compiler.
*   Standard template libraries including `<iostream>`, `<vector>`, `<string>`, and `<algorithm>`[cite: 1, 2, 4, 6].
*   The `<complex>` and `<cmath>` headers for mathematical operations in the FFT implementations[cite: 1, 2, 6].
