# AxioCryptoM v1

> Korean version: [README_KR.md](README_KR.md)

AxioCryptoM v1 is a library based on the KCMVP-certified cryptographic module AxioCrypto v2.1.0, providing PQC (NIST) and K-PQC algorithms for use on embedded MCU platforms.

It operates in both standard and TrustZone environments, delivering robust security features through KCMVP-certified cryptographic algorithms as well as PQC (NIST) and K-PQC algorithms.

Compatible with a wide range of MCUs including those from Nuvoton, STMicroelectronics, and more.

---

## Cryptographic Module

| Library | Module Name | Cert. No. | Cert. Date | Expiry Date | Developer | Module Type | KCMVP |
|---------------------|---------------------|----------|--------|------------|--------|----------|-------|
| AxioCryptoM v1 | AxioCrypto v2.1.0 | CM-280-2030.10 | 2025-10-14 | 2030-10-14 | Security Platform Inc. | F/W | Certified |
| [AxioCryptoM v2](https://github.com/OpenSPI/AxioCryptoM_v2) | AxioCrypto v2.2.0 | ➖ | ➖ | ➖ | Security Platform Inc. | F/W | In Preparation |



* AxioCryptoM v2 is preparing for KCMVP certification and will support more MCUs. [Learn more](https://github.com/OpenSPI/AxioCryptoM_v2)
---
## Supported Platforms
Refer to the README of each MCU line for details and usage instructions.

| # | Manufacturer | MCU Line | Part Number | Core | Board | KCMVP Cert. | Sample Code |
|:---:|--------|--------|--------|-----|------|-------------|------|
| 1 | Nuvoton | [M2351](M2351/project/README.md) | M2351ZIAAE | Cortex-M23 | Custom Board | ✅ | ✅ |
| 2 | Nuvoton | [M2351](M2351/project/README.md) | M2351SIAAE | Cortex-M23 | Custom Board | ✅ | ✅ |
| 3 | Nuvoton | [M2351](M2351/project/README.md) | M2351KIAAE | Cortex-M23 | NuMaker-PFM-M2351 | ✅ | ✅ |
| 4 | Nuvoton | [M2354](M2354/project/README.md) | M2354LJFAE | Cortex-M23 | Custom Board | ✅ | ✅ |
| 5 | Nuvoton | [M2354](M2354/project/README.md) | M2354SJFAE | Cortex-M23 | Custom Board | ✅ | ✅ |
| 6 | Nuvoton | [M2354](M2354/project/README.md) | M2354KJFAE | Cortex-M23 | NuMaker-PFM-M2354 | ✅ | ✅ |
| 7 | STMicroelectronics | [STM32H563-TZ](STM32H563-TZ/project/README.md) | STM32H563ZI | Cortex-M33 | NUCLEO-H563ZI | ✅ | ✅ |
| 8 | STMicroelectronics | STM32H562 | STM32H562VG | Cortex-M33 | Custom Board | ✅ | In Preparation |
| 9 | Renesas | RA6 | R7FA6M4AF3CFB | Cortex-M33 | Custom Board | ✅ | In Preparation |
| 10 | Renesas | RA6 | R7FA6M5BH3CFC | Cortex-M33 | Custom Board | ✅ | In Preparation |
| 11 | Renesas | RA6 | R7FA6E10F2CFP | Cortex-M33 | Custom Board | ✅ | In Preparation |
| 12 | Renesas | RA4 | R7FA4M2AD3CFP | Cortex-M33 | Custom Board | ✅ | In Preparation |
| 13 | Renesas | RA4 | R7FA4M3AF3CFB | Cortex-M33 | Custom Board | ✅ | In Preparation |
| 14 | Renesas | RA4 | R7FA4E10D2CFM | Cortex-M33 | Custom Board | ✅ | In Preparation |

## Supported Cryptographic Algorithms

| Manufacturer | MCU Line | PQC | ARIA | AES | LEA | SHA | HMAC | Random Generator | TRNG | ECDSA | ECDH | PBKDF2 | HKDF | Key Management |
|--------|--------|:----:|:----:|:---:|:---:|:-------:|:----:|:-----------:|:----:|:-----:|:----:|:------:|:----:|:------:|
| Nuvoton | M2351 | ➖ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Nuvoton | M2354 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| STMicroelectronics | STM32H563 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

| Item | Algorithms |
|------|--------------|
| PQC DSA (NIST) | ML-DSA-44 (Dilithium2), SLH-DSA-Shake128f (SPHINCS+), FN-DSA-512 (Falcon-512) |
| PQC KEM (NIST) | ML-KEM-512 (Kyber-512) |
| K-PQC DSA | AIMer-128f, HAETAE-2 |
| K-PQC KEM | NTRU-768, SMAUG-1 |
| ARIA | ARIA-128 / 192 / 256, CBC / CTR / GCM |
| AES | AES-128 / 192 / 256, CBC / CTR / GCM |
| LEA | LEA-128 / 192 / 256, CBC / CTR / GCM |
| SHA | SHA-256 |
| HMAC | HMAC-SHA-256 |
| Random Generator | Hash_DRBG (SHA-256) |
| TRNG | True Random Number Generator (Hardware RNG) |
| ECDSA | ECDSA P-256 |
| ECDH | ECDH P-256 |
| PBKDF2 | PBKDF2-HMAC-SHA-256 |
| HKDF | HKDF-SHA-256 |
| Key Management | Key Generation / Storage / Deletion / Retrieval |

---
## License
This library and sample source code may be freely used for personal purposes only.  
Commercial use, redistribution, modification, unauthorized copying, and reverse engineering are prohibited.  
For commercial licensing inquiries, please contact Security Platform Inc.

---

## Usage Restrictions

This AxioCryptoM library is a **public (Evaluation)** version and has limitations on the number of API calls.  
For lifting restrictions and commercial licensing inquiries, please contact Security Platform Inc.