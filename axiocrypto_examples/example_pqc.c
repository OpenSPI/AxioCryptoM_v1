#include <stdio.h>
#include <string.h>
#include "axiocrypto.h"
#include "axiocrypto_pqc.h"
#include "example_util.h"

#define PQC_MSG_MAX_SIZE    1024

int example_aimer128f(void)
{
    int ret = -1;

    uint8_t pk[PQC_AIMER128F_PUBLICKEY_SIZE] = {0x00,};
    uint8_t sk[PQC_AIMER128F_SECRETKEY_SIZE] = {0x00,};
    uint8_t sig[PQC_AIMER128F_SIGNATURE_SIZE] = {0x00,};
    size_t siglen = PQC_AIMER128F_SIGNATURE_SIZE;
    uint8_t msg[PQC_MSG_MAX_SIZE] = {0x00,};
    size_t msglen = PQC_MSG_MAX_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_AIMER128F, pk, PQC_AIMER128F_PUBLICKEY_SIZE, sk, PQC_AIMER128F_SECRETKEY_SIZE);
    if(ret != PQC_SUCCESS){
        printf("AIMER128F keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", PQC_AIMER128F_PUBLICKEY_SIZE);
		print_hex("PK:     ", pk, PQC_AIMER128F_PUBLICKEY_SIZE);
		printf("SK Len:%d\n", PQC_AIMER128F_SECRETKEY_SIZE);
		print_hex("SK:     ", sk, PQC_AIMER128F_SECRETKEY_SIZE);
#endif
		printf("[AIMER128F] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		init_ms_ticks();
		ret = axiocrypto_pqc_sign_signature(PQC_AIMER128F, sk, PQC_AIMER128F_SECRETKEY_SIZE, msg, msglen, sig, &siglen);
    if(ret != PQC_SUCCESS){
        printf("AIMER128F signing failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("sig Len:%d\n", siglen);
		print_hex("sig:     ", sig, siglen);
#endif
		printf("[AIMER128F] SIGN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		init_ms_ticks();
		ret = axiocrypto_pqc_verify(PQC_AIMER128F, pk, PQC_AIMER128F_PUBLICKEY_SIZE, msg, msglen, sig, siglen);
    if(ret != PQC_SUCCESS){
        printf("AIMER128F signature verification failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("msg Len:%d\n", msglen);
		print_hex("msg:     ", msg, msglen);
#endif
		printf("[AIMER128F] VERIFY\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_haetae2(void)
{
    int ret = -1;

    uint8_t pk[PQC_HAETAE2_PUBLICKEY_SIZE] = {0x00,};
    uint8_t sk[PQC_HAETAE2_SECRETKEY_SIZE] = {0x00,};
    uint8_t sig[PQC_HAETAE2_SIGNATURE_SIZE] = {0x00,};
    size_t siglen = PQC_HAETAE2_SIGNATURE_SIZE;
    uint8_t msg[PQC_MSG_MAX_SIZE] = {0x00,};
    size_t msglen = PQC_MSG_MAX_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_HAETAE2, pk, PQC_HAETAE2_PUBLICKEY_SIZE, sk, PQC_HAETAE2_SECRETKEY_SIZE);
    if(ret != PQC_SUCCESS){
        printf("HAETAE2 keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", PQC_HAETAE2_PUBLICKEY_SIZE);
		print_hex("PK:     ", pk, PQC_HAETAE2_PUBLICKEY_SIZE);
		printf("SK Len:%d\n", PQC_HAETAE2_SECRETKEY_SIZE);
		print_hex("SK:     ", sk, PQC_HAETAE2_SECRETKEY_SIZE);
#endif
		printf("[HAETAE2] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		init_ms_ticks();
		ret = axiocrypto_pqc_sign_signature(PQC_HAETAE2, sk, PQC_HAETAE2_SECRETKEY_SIZE, msg, msglen, sig, &siglen);
    if(ret != PQC_SUCCESS){
        printf("HAETAE2 signing failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("sig Len:%d\n", siglen);
		print_hex("sig:     ", sig, siglen);
#endif
		printf("[HAETAE2] SIGN\t\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		init_ms_ticks();
		ret = axiocrypto_pqc_verify(PQC_HAETAE2, pk, PQC_HAETAE2_PUBLICKEY_SIZE, msg, msglen, sig, siglen);
    if(ret != PQC_SUCCESS){
        printf("HAETAE2 signature verification failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("msg Len:%d\n", msglen);
		print_hex("msg:     ", msg, msglen);
#endif
		printf("[HAETAE2] VERIFY\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_dilithium2(void)
{
    int ret = -1;

    uint8_t pk[PQC_DILITHIUM2_PUBLICKEY_SIZE] = {0x00,};
    uint8_t sk[PQC_DILITHIUM2_SECRETKEY_SIZE] = {0x00,};
    uint8_t sig[PQC_DILITHIUM2_SIGNATURE_SIZE] = {0x00,};
    size_t siglen = PQC_DILITHIUM2_SIGNATURE_SIZE;
    uint8_t msg[PQC_MSG_MAX_SIZE] = {0x00,};
    size_t msglen = PQC_MSG_MAX_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_ML_DSA_44, pk, PQC_DILITHIUM2_PUBLICKEY_SIZE, sk, PQC_DILITHIUM2_SECRETKEY_SIZE);
    if(ret != PQC_SUCCESS){
        printf("DILITHIUM2 keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", PQC_DILITHIUM2_PUBLICKEY_SIZE);
		print_hex("PK:     ", pk, PQC_DILITHIUM2_PUBLICKEY_SIZE);
		printf("SK Len:%d\n", PQC_DILITHIUM2_SECRETKEY_SIZE);
		print_hex("SK:     ", sk, PQC_DILITHIUM2_SECRETKEY_SIZE);
#endif
		printf("[DILITHIUM2] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		init_ms_ticks();
		ret = axiocrypto_pqc_sign_signature(PQC_ML_DSA_44, sk, PQC_DILITHIUM2_SECRETKEY_SIZE, msg, msglen, sig, &siglen);
    if(ret != PQC_SUCCESS){
        printf("DILITHIUM2 signing failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("sig Len:%d\n", siglen);
		print_hex("sig:     ", sig, siglen);
#endif
		printf("[DILITHIUM2] SIGN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		init_ms_ticks();
		ret = axiocrypto_pqc_verify(PQC_ML_DSA_44, pk, PQC_DILITHIUM2_PUBLICKEY_SIZE, msg, msglen, sig, siglen);
    if(ret != PQC_SUCCESS){
        printf("DILITHIUM2 signature verification failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("msg Len:%d\n", msglen);
		print_hex("msg:     ", msg, msglen);
#endif
		printf("[DILITHIUM2] VERIFY\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    return ret;
}

int example_sphincs128f(void)
{
    int ret = -1;

    uint8_t pk[PQC_SPHINCS128F_PUBLICKEY_SIZE] = {0x00,};
    uint8_t sk[PQC_SPHINCS128F_SECRETKEY_SIZE] = {0x00,};
    uint8_t sig[PQC_SPHINCS128F_SIGNATURE_SIZE] = {0x00,};
    size_t siglen = PQC_SPHINCS128F_SIGNATURE_SIZE;
    uint8_t msg[PQC_MSG_MAX_SIZE] = {0x00,};
    size_t msglen = PQC_MSG_MAX_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_SLH_DSA_SHAKE128F, pk, PQC_SPHINCS128F_PUBLICKEY_SIZE, sk, PQC_SPHINCS128F_SECRETKEY_SIZE);
    if(ret != PQC_SUCCESS){
        printf("SPHINCS128F keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", PQC_SPHINCS128F_PUBLICKEY_SIZE);
		print_hex("PK:     ", pk, PQC_SPHINCS128F_PUBLICKEY_SIZE);
		printf("SK Len:%d\n", PQC_SPHINCS128F_SECRETKEY_SIZE);
		print_hex("SK:     ", sk, PQC_SPHINCS128F_SECRETKEY_SIZE);
#endif
		printf("[SPHINCS128F] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		init_ms_ticks();
		ret = axiocrypto_pqc_sign_signature(PQC_SLH_DSA_SHAKE128F, sk, PQC_SPHINCS128F_SECRETKEY_SIZE, msg, msglen, sig, &siglen);
    if(ret != PQC_SUCCESS){
        printf("SPHINCS128F signing failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("sig Len:%d\n", siglen);
		print_hex("sig:     ", sig, siglen);
#endif
		printf("[SPHINCS128F] SIGN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		init_ms_ticks();
		ret = axiocrypto_pqc_verify(PQC_SLH_DSA_SHAKE128F, pk, PQC_SPHINCS128F_PUBLICKEY_SIZE, msg, msglen, sig, siglen);
    if(ret != PQC_SUCCESS){
        printf("SPHINCS128F signature verification failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("msg Len:%d\n", msglen);
		print_hex("msg:     ", msg, msglen);
#endif
		printf("[SPHINCS128F] VERIFY\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_falcon512(void)
{
    int ret = -1;

    uint8_t pk[PQC_FALCON512_PUBLICKEY_SIZE] = {0x00,};
    uint8_t sk[PQC_FALCON512_SECRETKEY_SIZE] = {0x00,};
    uint8_t sig[PQC_MSG_MAX_SIZE + PQC_FALCON512_SIGNATURE_SIZE + 1024] = {0x00,};
    size_t siglen = PQC_MSG_MAX_SIZE + PQC_FALCON512_SIGNATURE_SIZE + 1024;
    uint8_t msg[PQC_MSG_MAX_SIZE] = {0x00,};
    size_t msglen = PQC_MSG_MAX_SIZE;

    uint8_t sm[PQC_MSG_MAX_SIZE + PQC_FALCON512_SIGNATURE_SIZE + 1024] = {0x00,};
    size_t smlen = PQC_MSG_MAX_SIZE + PQC_FALCON512_SIGNATURE_SIZE + 1024;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_FN_DSA_512, pk, PQC_FALCON512_PUBLICKEY_SIZE, sk, PQC_FALCON512_SECRETKEY_SIZE);
    if(ret != PQC_SUCCESS){
        printf("FALCON512 keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", PQC_FALCON512_PUBLICKEY_SIZE);
		print_hex("PK:     ", pk, PQC_FALCON512_PUBLICKEY_SIZE);
		printf("SK Len:%d\n", PQC_FALCON512_SECRETKEY_SIZE);
		print_hex("SK:     ", sk, PQC_FALCON512_SECRETKEY_SIZE);
#endif
		printf("[FALCON512] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		siglen = PQC_MSG_MAX_SIZE + PQC_FALCON512_SIGNATURE_SIZE + 1024;
		init_ms_ticks();
    ret = axiocrypto_pqc_sign(PQC_FN_DSA_512, sk, PQC_FALCON512_SECRETKEY_SIZE, msg, msglen, sig, &siglen);
    if(ret != PQC_SUCCESS){
        printf("FALCON512 signing failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("sig Len:%d\n", siglen);
		print_hex("sig:     ", sig, siglen);
#endif
		printf("[FALCON512] SIGN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		memcpy(sm, sig, siglen);
    smlen = siglen;
    msglen = PQC_MSG_MAX_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_open(PQC_FN_DSA_512, pk, PQC_FALCON512_PUBLICKEY_SIZE, sm, smlen, msg, &msglen);
    if(ret != PQC_SUCCESS){
        printf("FALCON512 signature verification failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("msg Len:%d\n", msglen);
		print_hex("msg:     ", msg, msglen);
#endif
		printf("[FALCON512] VERIFY\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_kyber512(void)
{
    int ret = -1;

    uint8_t sk[PQC_KYBER512_SECRETKEY_SIZE] = {0x00,};
    size_t sklen = PQC_KYBER512_SECRETKEY_SIZE;
    uint8_t pk[PQC_KYBER512_PUBLICKEY_SIZE] = {0x00,};
    size_t pklen = PQC_KYBER512_PUBLICKEY_SIZE;
    uint8_t ct[PQC_KYBER512_CIPHERTEXT_SIZE] = {0x00,};
    size_t ctlen = PQC_KYBER512_CIPHERTEXT_SIZE;
    uint8_t ss1[PQC_KYBER512_SHAREDSECRET_SIZE] = {0x00,};
    size_t ss1len = PQC_KYBER512_SHAREDSECRET_SIZE;
    uint8_t ss2[PQC_KYBER512_SHAREDSECRET_SIZE] = {0x00,};
    size_t ss2len = PQC_KYBER512_SHAREDSECRET_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_ML_KEM_512, pk, pklen, sk, sklen);
    if(ret != PQC_SUCCESS){
        printf("KYBER512 keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", pklen);
		print_hex("PK:     ", pk, pklen);
		printf("SK Len:%d\n", sklen);
		print_hex("SK:     ", sk, sklen);
#endif
		printf("[KYBER512] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		ctlen = PQC_KYBER512_CIPHERTEXT_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_encapsulate(PQC_ML_KEM_512, pk, pklen, ct, &ctlen, ss1, ss1len);
    if(ret != PQC_SUCCESS){
        printf("KYBER512 encapsulation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("CT Len:%d\n", ctlen);
		print_hex("CT:     ", ct, ctlen);
		printf("SS1 Len:%d\n", ss1len);
		print_hex("SS1:     ", ss1, ss1len);
#endif
		printf("[KYBER512] ENCAP\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		ss2len = PQC_KYBER512_SHAREDSECRET_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_decapsulate(PQC_ML_KEM_512, sk, sklen, ct, ctlen, ss2, &ss2len);
    if(ret != PQC_SUCCESS){
        printf("KYBER512 decapsulation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("SS2 Len:%d\n", ss2len);
		print_hex("SS2:     ", ss2, ss2len);
#endif
		printf("[KYBER512] DECAP\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_ntru768(void)
{
    int ret = -1;

    uint8_t sk[PQC_NTRU768_SECRETKEY_SIZE] = {0x00,};
    size_t sklen = PQC_NTRU768_SECRETKEY_SIZE;
    uint8_t pk[PQC_NTRU768_PUBLICKEY_SIZE] = {0x00,};
    size_t pklen = PQC_NTRU768_PUBLICKEY_SIZE;
    uint8_t ct[PQC_NTRU768_CIPHERTEXT_SIZE] = {0x00,};
    size_t ctlen = PQC_NTRU768_CIPHERTEXT_SIZE;
    uint8_t ss1[PQC_NTRU768_SHAREDSECRET_SIZE] = {0x00,};
    size_t ss1len = PQC_NTRU768_SHAREDSECRET_SIZE;
    uint8_t ss2[PQC_NTRU768_SHAREDSECRET_SIZE] = {0x00,};
    size_t ss2len = PQC_NTRU768_SHAREDSECRET_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_NTRU768, pk, pklen, sk, sklen);
    if(ret != PQC_SUCCESS){
        printf("NTRU768 keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", pklen);
		print_hex("PK:     ", pk, pklen);
		printf("SK Len:%d\n", sklen);
		print_hex("SK:     ", sk, sklen);
#endif
		printf("[NTRU768] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		ctlen = PQC_NTRU768_CIPHERTEXT_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_encapsulate(PQC_NTRU768, pk, pklen, ct, &ctlen, ss1, ss1len);
    if(ret != PQC_SUCCESS){
        printf("NTRU768 encapsulation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("CT Len:%d\n", ctlen);
		print_hex("CT:     ", ct, ctlen);
		printf("SS1 Len:%d\n", ss1len);
		print_hex("SS1:     ", ss1, ss1len);
#endif
		printf("[NTRU768] ENCAP\t\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		ss2len = PQC_NTRU768_SHAREDSECRET_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_decapsulate(PQC_NTRU768, sk, sklen, ct, ctlen, ss2, &ss2len);
    if(ret != PQC_SUCCESS){
        printf("NTRU768 decapsulation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("SS2 Len:%d\n", ss2len);
		print_hex("SS2:     ", ss2, ss2len);
#endif
		printf("[NTRU768] DECAP\t\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_smaug1(void)
{
    int ret = -1;

    uint8_t sk[PQC_SMAUG1_SECRETKEY_SIZE] = {0x00,};
    size_t sklen = PQC_SMAUG1_SECRETKEY_SIZE;
    uint8_t pk[PQC_SMAUG1_PUBLICKEY_SIZE] = {0x00,};
    size_t pklen = PQC_SMAUG1_PUBLICKEY_SIZE;
    uint8_t ct[PQC_SMAUG1_CIPHERTEXT_SIZE] = {0x00,};
    size_t ctlen = PQC_SMAUG1_CIPHERTEXT_SIZE;
    uint8_t ss1[PQC_SMAUG1_SHAREDSECRET_SIZE] = {0x00,};
    size_t ss1len = PQC_SMAUG1_SHAREDSECRET_SIZE;
    uint8_t ss2[PQC_SMAUG1_SHAREDSECRET_SIZE] = {0x00,};
    size_t ss2len = PQC_SMAUG1_SHAREDSECRET_SIZE;

		init_ms_ticks();
    ret = axiocrypto_pqc_keypair(PQC_SMAUG1, pk, pklen, sk, sklen);
    if(ret != PQC_SUCCESS){
        printf("SMAUG1 keypair generation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("PK Len:%d\n", pklen);
		print_hex("PK:     ", pk, pklen);
		printf("SK Len:%d\n", sklen);
		print_hex("SK:     ", sk, sklen);
#endif
		printf("[SMAUG1] KEYGEN\t\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		ctlen = PQC_SMAUG1_CIPHERTEXT_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_encapsulate(PQC_SMAUG1, pk, pklen, ct, &ctlen, ss1, ss1len);
    if(ret != PQC_SUCCESS){
        printf("SMAUG1 encapsulation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("CT Len:%d\n", ctlen);
		print_hex("CT:     ", ct, ctlen);
		printf("SS1 Len:%d\n", ss1len);
		print_hex("SS1:     ", ss1, ss1len);
#endif
		printf("[SMAUG1] ENCAP\t\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		ss2len = PQC_SMAUG1_SHAREDSECRET_SIZE;
		init_ms_ticks();
    ret = axiocrypto_pqc_decapsulate(PQC_SMAUG1, sk, sklen, ct, ctlen, ss2, &ss2len);
    if(ret != PQC_SUCCESS){
        printf("SMAUG1 decapsulation failed(ret:%d)\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
		printf("SS2 Len:%d\n", ss2len);
		print_hex("SS2:     ", ss2, ss2len);
#endif
		printf("[SMAUG1] DECAP\t\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    return ret;
}

int example_pqc(const char *arg)
{
		int ret = -1;
    
		printf("\n");
		printf("========================================\n");
		printf("*   AxioCrypto PQC Examples       *\n");
		printf("========================================\n\n");
    
		// Initialize AxioCrypto library
		printf("Initializing AxioCrypto library...\n");
		ret = axiocrypto_init(NULL, 0);
		if (ret != CRYPTO_SUCCESS && ret != CRYPTO_ERR_ALREADY_INIT) {
				printf("ERROR: axiocrypto_init failed with code %d\n", ret);
				return -1;
		}
		if (ret == CRYPTO_ERR_ALREADY_INIT) {
				printf("INFO: AxioCrypto already initialized\n\n");
		} else {
				printf("SUCCESS: AxioCrypto initialized\n\n");
		}
		
    if(!strcmp(arg, "all")){
				if((ret = example_aimer128f())) return ret;
				if((ret = example_haetae2())) return ret;
				if((ret = example_dilithium2())) return ret;
				if((ret = example_sphincs128f())) return ret;
				if((ret = example_falcon512())) return ret;
				if((ret = example_kyber512())) return ret;
				if((ret = example_ntru768())) return ret;
				if((ret = example_smaug1())) return ret;
		} else if (!strcmp(arg, "aimer128f")){
				if((ret = example_aimer128f())) return ret;
		} else if (!strcmp(arg, "haetae2")){
				if((ret = example_haetae2())) return ret;
		} else if (!strcmp(arg, "dilithium2")){
				if((ret = example_dilithium2())) return ret;
		} else if (!strcmp(arg, "sphincs128f")){
				if((ret = example_sphincs128f())) return ret;
		} else if (!strcmp(arg, "falcon512")){
				if((ret = example_falcon512())) return ret;
		} else if (!strcmp(arg, "kyber512")){
				if((ret = example_kyber512())) return ret;
		} else if (!strcmp(arg, "ntru768")){
				if((ret = example_ntru768())) return ret;
		} else if (!strcmp(arg, "smaug1")){
				if((ret = example_smaug1())) return ret;
		} else {
				printf("Unsupported Option\n");
				return -1;
		}

		printf("\n");
		printf("========================================\n");
		printf("PQC examples completed successfully!\n");
		printf("========================================\n\n");
	
		return 0;
}
