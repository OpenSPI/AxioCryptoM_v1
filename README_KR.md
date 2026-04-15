# AxioCryptoM v1

> English version: [README.md](README.md)

AxioCryptoM v1은 KCMVP 검증필 암호모듈 AxioCrypto v2.1.0을 기반으로 PQC(NIST), K-PQC 알고리즘을 임베디드 MCU 플랫폼에서 사용할 수 있도록 제공하는 라이브러리입니다.

일반 및 TrustZone 환경에서 동작하며, KCMVP 검증필 암호 알고리즘과 PQC(NIST), K-PQC 알고리즘을 통해 강력한 보안 기능을 제공합니다.

Nuvoton, STMicroelectronics 등을 포함한 다수의 MCU에서 사용이 가능합니다.

---

## 암호모듈

|라이브러리| 암호모듈명 | 검증번호 | 검증일 | 효력만료일 | 개발사 | 모듈형태 | KCMVP | 
|---------------------|---------------------|----------|--------|------------|--------|----------|-------|
|AxioCryptoM v1| AxioCrypto v2.1.0 | CM-280-2030.10 | 2025-10-14 | 2030-10-14 | 시큐리티플랫폼㈜ | F/W | 검증필 |
|[AxioCryptoM v2](https://github.com/OpenSPI/AxioCryptoM_v2)| AxioCrypto v2.2.0 | ➖ | ➖ | ➖ | 시큐리티플랫폼㈜ | F/W | 검증예정 |




* AxioCryptoM v2는 KCMVP 인증을 준비 중이며, 더 많은 MCU를 지원할 예정입니다. [자세히 보기](https://github.com/OpenSPI/AxioCryptoM_v2)
---

## 지원 플랫폼
상세 내용 및 사용방법은 각 MCU라인의 README를 참고하십시오.

| # | 제조사 | MCU 라인 | 파트넘버 | 코어 | 보드 | KCMVP 검증 | 샘플 코드 |
|:---:|--------|--------|--------|-----|------|-------------|------|
| 1 |Nuvoton| [M2351](M2351/project/README.md) | M2351ZIAAE | Cortex-M23 | Custom Board| ✅ |✅ |
| 2 |Nuvoton| [M2351](M2351/project/README.md) | M2351SIAAE | Cortex-M23 | Custom Board| ✅ |✅ |
| 3 |Nuvoton| [M2351](M2351/project/README.md) | M2351KIAAE | Cortex-M23 | NuMaker-PFM-M2351| ✅|✅ |
| 4 |Nuvoton| [M2354](M2354/project/README.md) | M2354LJFAE | Cortex-M23 | Custom Board| ✅|✅ |
| 5 |Nuvoton| [M2354](M2354/project/README.md) | M2354SJFAE | Cortex-M23 | Custom Board| ✅|✅ |
| 6 |Nuvoton| [M2354](M2354/project/README.md) | M2354KJFAE | Cortex-M23 | NuMaker-PFM-M2354| ✅|✅ |
| 7 |STMicroelectronics| [STM32H563-TZ](STM32H563-TZ/project/README.md) | STM32H563ZI | Cortex-M33 | NUCLEO-H563ZI| ✅|✅ |
| 8 |STMicroelectronics| STM32H562 | STM32H562VG | Cortex-M33 | Custom Board| ✅|예정 |
| 9 |Renesas| RA6 | R7FA6M4AF3CFB | Cortex-M33 | Custom Board| ✅|예정 |
| 10 |Renesas| RA6 | R7FA6M5BH3CFC | Cortex-M33 | Custom Board| ✅|예정 |
| 11 |Renesas| RA6 | R7FA6E10F2CFP | Cortex-M33 | Custom Board| ✅|예정 |
| 12 |Renesas| RA4 | R7FA4M2AD3CFP | Cortex-M33 | Custom Board| ✅|예정 |
| 13 |Renesas| RA4 | R7FA4M3AF3CFB | Cortex-M33 | Custom Board| ✅|예정 |
| 14 |Renesas| RA4 | R7FA4E10D2CFM | Cortex-M33 | Custom Board| ✅|예정 |

## 지원 암호 알고리즘

| 제조사 | MCU 라인 | PQC | ARIA | AES | LEA | SHA | HMAC | Random Generator | TRNG | ECDSA | ECDH | PBKDF2 | HKDF | Key Management |
|--------|--------|:----:|:----:|:---:|:---:|:-------:|:----:|:-----------:|:----:|:-----:|:----:|:------:|:----:|:------:|
| Nuvoton | M2351 | ➖ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Nuvoton | M2354 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| STMicroelectronics | STM32H563 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

| 항목 | 세부 알고리즘 |
|------|--------------|
| PQC DSA(NIST) | ML-DSA-44 (Dilithium2), SLH-DSA-Shake128f (SPHINCS+), FN-DSA-512 (Falcon-512) |
| PQC KEM(NIST) | ML-KEM-512 (Kyber-512) |
| K-PQC DSA | AIMer-128f, HAETAE-2 |
| K-PQC KEM | NTRU-768, SMAUG-1 |
| ARIA | ARIA-128 / 192 / 256, CBC / CTR / GCM |
| AES | AES-128 / 192 / 256, CBC / CTR / GCM |
| LEA | LEA-128 / 192 / 256, CBC / CTR / GCM |
| SHA | SHA-256 |
| HMAC | HMAC-SHA-256 |
| Random Generator | Hash_DRBG (SHA-256) |
| TRNG | True Random Number Generator (하드웨어 난수 발생기) |
| ECDSA | ECDSA P-256 |
| ECDH | ECDH P-256 |
| PBKDF2 | PBKDF2-HMAC-SHA-256 |
| HKDF | HKDF-SHA-256 |
| Key Management | 키 생성 / 저장 / 삭제 / 조회 |

---
## 라이선스
본 라이브러리 및 예제 소스는 개인적 용도에 한해 자유롭게 사용할 수 있습니다.  
상업적 사용, 재배포, 수정, 무단 복제, 리버스 엔지니어링은 금지됩니다.  
상용 라이선스 문의는 시큐리티플랫폼㈜으로 연락해주십시오.

---

## 사용 제한

본 AxioCryptoM 라이브러리는 **공개용(Evaluation)** 버전으로, API 사용 횟수에 제한이 있습니다.  
제한 해제 및 상용 라이선스 문의는 시큐리티플랫폼㈜으로 연락해주십시오.