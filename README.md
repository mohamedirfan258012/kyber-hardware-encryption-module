# Post-Quantum Hardware Encryption Module using Kyber
Embedded Security | Post-Quantum Cryptography | Kyber KEM

This project implements a **Post-Quantum Cryptography (PQC) hardware encryption module** using the **Kyber lattice-based Key Encapsulation Mechanism (KEM)** on an STM32F407 microcontroller.

## Hardware
STM32F407 Microcontroller

## Development Environment
Arduino IDE with STM32 board support.

Board Manager URL used:
https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json

## Features
• Lattice-based post-quantum encryption  
• Kyber Key Encapsulation Mechanism implementation  
• Embedded implementation on STM32F407  
• Lightweight cryptographic processing

## How to Run
1 Install STM32 boards in Arduino IDE  
2 Select STM32F407 board  
3 Upload `kyber.ino`  
4 Open Serial Monitor to see output

## Applications
• Secure IoT devices  
• Quantum-resistant communication  
• Embedded cybersecurity systems

## Project Structure
```
kyber-hardware-encryption-module
│
├── kyber.ino            Main firmware for STM32F407
├── kem.c / kem.h        Kyber Key Encapsulation Mechanism
├── indcpa.c / indcpa.h  CPA-secure encryption implementation
├── poly.c / poly.h      Polynomial arithmetic operations
├── polyvec.c / polyvec.h Vector polynomial operations
├── ntt.c / ntt.h        Number Theoretic Transform
├── reduce.c / reduce.h  Modular reduction functions
├── randombytes.c / randombytes.h Random number generation
├── fips202.c / fips202.h SHA3 / Keccak cryptographic primitives
├── symmetric-shake.c    Symmetric cryptographic functions
└── verify.c / verify.h  Verification operations
```


