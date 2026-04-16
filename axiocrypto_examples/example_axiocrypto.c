#include <stdio.h>
#include <string.h>
#include "axiocrypto.h"
#include "example_util.h"

#if defined(__AXIOCRYPTO_M2354__) || defined(__AXIOCRYPTO_M2351__)
#else
#include <stm32h5xx_hal.h>
#endif

int example_axiocrypto_drbg(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    uint8_t buf[32];

    init_ms_ticks();
    ret = axiocrypto_random(buf, 32);
    if (ret != CRYPTO_SUCCESS) {
	    printf("FAIL: axiocrypto_random %d\n\r", ret);
	    return ret;
    }
#ifdef __DEBUG_HEX
    printf("DRBG Len:%d\n", 32);
    print_hex("DRBG:     ", buf, 32);
#endif
    printf("[DRBG] RANDOM\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    return ret;
}

int example_axiocrypto_aria_gcm(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    ctx_handle_t handle = {0,};

    uint8_t aad_128[16] = {
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF,
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF
    };
    uint8_t tag[16];

    uint8_t key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    uint32_t key_len = 16;
    
    uint8_t iv[16] = {
        0xCA, 0xFE, 0xBA, 0xBE, 0xFA, 0xCE, 0xDB, 0xAD,
        0xDB, 0xAD, 0xDE, 0xCA, 0xF8, 0x88, 0xDE, 0xCA
    };
    uint32_t iv_len = 16;
    
    uint8_t plain_msg[] = "Hello, AxioCrypto! This is ARIA-GCM example.";
    uint32_t plain_msg_len = sizeof(plain_msg) - 1;
    
    uint8_t encrypt_msg[128] = {0,};
    uint32_t encrypt_msg_len = sizeof(encrypt_msg);
    
    uint8_t decrypt_msg[128] = {0,};
    uint32_t decrypt_msg_len = sizeof(decrypt_msg);

    sprintf((char*)handle, "example_aria_handle");

    ret = axiocrypto_allocate_slot(handle, SYM_ARIA, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_sym_putkey(handle, key, key_len, 0, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_putkey %d\n\r", ret);
        return ret;
    }

    init_ms_ticks();
    ret = axiocrypto_sym_enc_GCM(handle, SYM_ARIA, plain_msg, plain_msg_len, aad_128, sizeof(aad_128), tag, sizeof(tag), iv, iv_len, encrypt_msg, &encrypt_msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_enc_GCM %d\n\r", ret);
		return ret;
    }
#ifdef __DEBUG_HEX
    printf("Enc Len:%d\n", encrypt_msg_len);
    print_hex("Enc:     ", encrypt_msg, encrypt_msg_len);
#endif
    printf("[ARIA] ENCRYPT\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    ret = axiocrypto_free_slot(handle, SYM_ARIA);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_allocate_slot(handle, SYM_ARIA, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_sym_putkey(handle, key, key_len, 0, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_putkey %d\n\r", ret);
        return ret;
    }

    init_ms_ticks();
    ret = axiocrypto_sym_dec_GCM(handle, SYM_ARIA, encrypt_msg, encrypt_msg_len, aad_128, sizeof(aad_128), tag, sizeof(tag), iv, iv_len, decrypt_msg, &decrypt_msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_dec_GCM %d\n\r", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("Dec Len:%d\n", decrypt_msg_len);
    print_hex("Dec:     ", decrypt_msg, decrypt_msg_len);
#endif
    printf("[ARIA] DECRYPT\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    ret = axiocrypto_free_slot(handle, SYM_ARIA);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }

    if(plain_msg_len != decrypt_msg_len){
        printf("FAIL: length\n\r");
        return CRYPTO_ERROR;
    }

    if(memcmp(plain_msg, decrypt_msg, plain_msg_len) != 0){
        printf("FAIL: message\n\r");
        return CRYPTO_ERROR;
    }

    return ret;
}

int example_axiocrypto_lea_gcm(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    ctx_handle_t handle = {0,};

    uint8_t aad_128[16] = {
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF,
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF
    };
    uint8_t tag[16];

    uint8_t key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    uint32_t key_len = 16;
    
    uint8_t iv[16] = {
        0xCA, 0xFE, 0xBA, 0xBE, 0xFA, 0xCE, 0xDB, 0xAD,
        0xDB, 0xAD, 0xDE, 0xCA, 0xF8, 0x88, 0xDE, 0xCA
    };
    uint32_t iv_len = 16;
    
    uint8_t plain_msg[] = "Hello, AxioCrypto! This is LEA-GCM example.";
    uint32_t plain_msg_len = sizeof(plain_msg) - 1;
    
    uint8_t encrypt_msg[128] = {0,};
    uint32_t encrypt_msg_len = sizeof(encrypt_msg);
    
    uint8_t decrypt_msg[128] = {0,};
    uint32_t decrypt_msg_len = sizeof(decrypt_msg);

    sprintf((char*)handle, "example_lea_handle");

    ret = axiocrypto_allocate_slot(handle, SYM_LEA, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_sym_putkey(handle, key, key_len, 0, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_putkey %d\n\r", ret);
        return ret;
    }

    init_ms_ticks();
    ret = axiocrypto_sym_enc_GCM(handle, SYM_LEA, plain_msg, plain_msg_len, aad_128, sizeof(aad_128), tag, sizeof(tag), iv, iv_len, encrypt_msg, &encrypt_msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_enc_GCM %d\n\r", ret);
		return ret;
    }
#ifdef __DEBUG_HEX
    printf("Enc Len:%d\n", encrypt_msg_len);
    print_hex("Enc:     ", encrypt_msg, encrypt_msg_len);
#endif
    printf("[LEA] ENCRYPT\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    ret = axiocrypto_free_slot(handle, SYM_LEA);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_allocate_slot(handle, SYM_LEA, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_sym_putkey(handle, key, key_len, 0, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_putkey %d\n\r", ret);
        return ret;
    }

    init_ms_ticks();
    ret = axiocrypto_sym_dec_GCM(handle, SYM_LEA, encrypt_msg, encrypt_msg_len, aad_128, sizeof(aad_128), tag, sizeof(tag), iv, iv_len, decrypt_msg, &decrypt_msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_dec_GCM %d\n\r", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("Dec Len:%d\n", decrypt_msg_len);
    print_hex("Dec:     ", decrypt_msg, decrypt_msg_len);
#endif
    printf("[LEA] DECRYPT\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    ret = axiocrypto_free_slot(handle, SYM_LEA);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }

    if(plain_msg_len != decrypt_msg_len){
        printf("FAIL: length\n\r");
        return CRYPTO_ERROR;
    }

    if(memcmp(plain_msg, decrypt_msg, plain_msg_len) != 0){
        printf("FAIL: message\n\r");
        return CRYPTO_ERROR;
    }

    return ret;
}

int example_axiocrypto_aes_gcm(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    ctx_handle_t handle;
    
    // Test data
    uint8_t aes_key[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };
    uint8_t plaintext[] = "Hello, AxioCrypto! This is AES-GCM example.";
    uint32_t pt_len = sizeof(plaintext) - 1; // Exclude null terminator
    
    uint8_t ciphertext[128] = {0,};
    uint32_t ct_len = sizeof(ciphertext);
    
    uint8_t decrypted[128] = {0,};
    uint32_t dec_len = sizeof(decrypted);
    
    uint8_t iv[12] = {
        0xCA, 0xFE, 0xBA, 0xBE, 0xFA, 0xCE,
        0xDB, 0xAD, 0xDE, 0xCA, 0xF8, 0x88
    };
    
    uint8_t aad[16] = {
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF,
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF
    };
    
    uint8_t tag[16];
    uint32_t tag_len = 16;
    
    sprintf((char*)handle, "example_aes_handle");
    
    ret = axiocrypto_allocate_slot(handle, SYM_AES, CTX_ATTR_NONE);
    if (ret != CRYPTO_SUCCESS) {
        printf("ERROR: axiocrypto_allocate_slot failed with code %d\n", ret);
        return ret;
    }
    
    ret = axiocrypto_sym_putkey(handle, aes_key, sizeof(aes_key), 0, CTX_ATTR_NONE);
    if (ret != CRYPTO_SUCCESS) {
        printf("ERROR: axiocrypto_sym_putkey failed with code %d\n", ret);
        return ret;
    }
		
		init_ms_ticks();
    ret = axiocrypto_sym_enc_GCM(handle, SYM_AES, plaintext, pt_len, aad, sizeof(aad), tag, tag_len, iv, sizeof(iv), ciphertext, &ct_len);
    if (ret != CRYPTO_SUCCESS) {
        printf("ERROR: axiocrypto_sym_enc_GCM failed with code %d\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("Enc Len:%d\n", ct_len);
    print_hex("Enc:     ", ciphertext, ct_len);
#endif
    printf("[AES] ENCRYPT\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		init_ms_ticks();
    ret = axiocrypto_sym_dec_GCM(handle, SYM_AES, ciphertext, ct_len, aad, sizeof(aad), tag, tag_len, iv, sizeof(iv), decrypted, &dec_len);
    if (ret != CRYPTO_SUCCESS) {
        printf("ERROR: axiocrypto_sym_dec_GCM failed with code %d\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("Dec Len:%d\n", dec_len);
    print_hex("Dec:     ", decrypted, dec_len);
#endif
    printf("[AES] DECRYPT\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
    
    if (dec_len != pt_len && memcmp(plaintext, decrypted, pt_len) != 0) {
        printf("FAIL: Decryption verification failed!\n\n");
    }
    
    ret = axiocrypto_free_slot(handle, SYM_AES);
    if (ret != CRYPTO_SUCCESS) {
        printf("ERROR: axiocrypto_free_slot failed with code %d\n", ret);
        return ret;
    }
    
    return ret;
}

int example_axiocrypto_hash(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    ctx_handle_t handle = {0,};

    uint8_t msg[] = "Hello, AxioCrypto! This is HASH example.";
    uint32_t msg_len = sizeof(msg) - 1;

    uint8_t digest[32] = {0,};

    sprintf((char*)handle, "example_hash_handle");

    init_ms_ticks();
    ret = axiocrypto_hash_init(handle, HASH_SHA_256);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL : axiocrypto_hash_init %d\n\r", ret);
        return ret;
    }
        
    ret = axiocrypto_hash_update(handle, msg, msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL : axiocrypto_hash_update %d\n\r", ret);
        return ret;
    }
        
    ret = axiocrypto_hash_final(handle, digest, 32);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL : axiocrypto_hash_final %d\n\r", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("Hash Len:%d\n", 32);
    print_hex("Hash:     ", digest, 32);
#endif
    printf("[HASH] SHA256\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
   
    return ret;
}

int example_axiocrypto_hmac(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;

    uint8_t digest[32] = {0,};
    uint32_t digest_len = sizeof(digest);

    uint8_t key[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };
    uint32_t key_len = sizeof(key);

    uint8_t msg[] = "Hello, AxioCrypto! This is HMAC example.";
    uint32_t msg_len = sizeof(msg) - 1;

    init_ms_ticks();
    ret = axiocrypto_hmac(HMAC_SHA_256, key, key_len, msg, msg_len, digest, digest_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL : axiocrypto_hmac %d\n\r", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("HMAC Len:%d\n", 32);
    print_hex("HMAC:     ", digest, 32);
#endif
    printf("[HMAC] SHA256\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    return ret;
}

int example_axiocrypto_ecdsa(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    ctx_handle_t handle = {0,};
    int rdonly = 0;
    uint8_t msg[32] = {0,};
    uint8_t sig[64] = {0,};
    uint32_t siglen = 64;
    uint8_t key[64] = {0,};
    uint32_t keylen = 64;

    axiocrypto_random(handle, sizeof(handle));

    ret = axiocrypto_allocate_slot(handle, ASYM_ECDSA_P256, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

		init_ms_ticks();
    ret = axiocrypto_asym_genkey(handle, ASYM_ECDSA_P256, rdonly);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_genkey %d\n\r", ret);
        return ret;
    }
    printf("[ECDSA] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		init_ms_ticks();
    ret = axiocrypto_asym_sign(handle, msg, 32, RAW_MSG, sig, &siglen);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_sign %d\n\r", ret);
        return ret;
    }
    printf("[ECDSA] SIGN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

		init_ms_ticks();
    siglen = 64;
    ret = axiocrypto_asym_verify(handle, msg, 32, RAW_MSG,  sig, siglen);
    if(ret != CRYPTO_SIG_ACCEPT && ret != CRYPTO_SIG_REJECT){
        printf("FAIL: axiocrypto_asym_verify %d\n\r", ret);
        return ret;
    }
    printf("[ECDSA] VERIFY\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    ret = axiocrypto_asym_getkey(handle, ASYM_ECDSA_P256, key, keylen);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_getkey %d\n\r", ret);
        return ret;
    }
		
    ret = axiocrypto_free_slot(handle, ASYM_ECDSA_P256);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }

    return ret;
}

int example_axiocrypto_ecdh(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    ctx_handle_t handle0 = {0,};
    ctx_handle_t handle1 = {0,};
    uint32_t algo = ASYM_ECDH_P256;
    int rdonly = CTX_ATTR_NONE;
    uint8_t kt0[64], kt1[64];
    uint8_t key0[64], key1[64];

		axiocrypto_random(handle0, sizeof(handle0));
		axiocrypto_random(handle1, sizeof(handle1));

    ret = axiocrypto_allocate_slot(handle0, ASYM_ECDH_P256, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_allocate_slot(handle1, ASYM_ECDH_P256, CTX_ATTR_NONE);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return ret;
    }

		init_ms_ticks();
    ret = axiocrypto_ecdh_genkey(handle0, algo, rdonly);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_genkey %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_ecdh_getkey(handle0, kt0, 64);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_getkey %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_ecdh_genkey(handle1, algo, rdonly);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_genkey %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_ecdh_getkey(handle1, kt1, 64);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_asym_getkey %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_ecdh_computekey(handle0, kt1, 64, key0, 64);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_ecdh_computekey %d\n\r", ret);
        return ret;
    }

    ret = axiocrypto_ecdh_computekey(handle1, kt0, 64, key1, 64);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_ecdh_computekey %d\n\r", ret);
        return ret;
    }
		printf("[ECDH] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());

    if (memcmp(key0, key1, 64) != 0) {
        printf("FAIL: axiocrypto_ecdh_computekey compare %d\n\r", ret);
        return CRYPTO_ERROR;
    } 

    ret = axiocrypto_free_slot(handle0, ASYM_ECDH_P256);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }
    ret = axiocrypto_free_slot(handle1, ASYM_ECDH_P256);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return ret;
    }

    return ret;
}

int example_axiocrypto_pbkdf(void)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    uint8_t pw[] = "pbkdf_password";
    uint32_t pwsz = sizeof(pw);
    uint8_t salt[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };
		uint32_t saltsz = 32;
    uint32_t iter = 1000;
    uint8_t key[32] = {0,};
		
		init_ms_ticks();
    ret = axiocrypto_pbkdf(pw, pwsz, salt, saltsz, iter, key, 32);
    if (ret != 0) {
        printf("FAIL: axiocrypto_pbkdf, %d\n", ret);
        return ret;
    }
#ifdef __DEBUG_HEX
    printf("PBKDF Len:%d\n", 32);
    print_hex("PBKDF:     ", key, 32);
#endif
		printf("[PBKDF] KEYGEN\t: PASS (%" PRIu32 " ms)\n", get_ms_ticks());
		
		return ret;
}

int example_axiocrypto(const char *arg)
{
    CRYPTO_STATUS ret;

    printf("\n");
    printf("========================================\n");
    printf("*      AxioCrypto Examples            *\n");
    printf("========================================\n\n");

    printf("Initializing AxioCrypto library...\n");
    ret = axiocrypto_init(NULL, 0);
    if (ret != CRYPTO_SUCCESS && ret != CRYPTO_ERR_ALREADY_INIT) {
        printf("ERROR: axiocrypto_init failed with code %d\n", ret);
        return ret;
    }

    if (ret == CRYPTO_ERR_ALREADY_INIT) {
        printf("INFO: AxioCrypto already initialized\n\n");
    } else {
        printf("SUCCESS: AxioCrypto initialized\n\n");
    }

    char ver[128] = {0};
    operation_mode_t opmode = OP_MODE_NOTHING;
    ret = axiocrypto_info(ver, sizeof(ver), &opmode);
    if(ret != CRYPTO_SUCCESS){
        printf("failed to get axiocrypto operation mode");
        return ret;
    }

    if(!strcmp(arg, "all")){
				if((ret = example_axiocrypto_drbg())) return ret;
				if((ret = example_axiocrypto_aria_gcm())) return ret;
				if((ret = example_axiocrypto_lea_gcm())) return ret;
				
				if(opmode == OP_MODE_NON_APPROVED){
					if((ret = example_axiocrypto_aes_gcm())) return ret;
				}
				if((ret = example_axiocrypto_hash())) return ret;
				if((ret = example_axiocrypto_hmac())) return ret;
				if((ret = example_axiocrypto_pbkdf())) return ret;
				if((ret = example_axiocrypto_ecdsa())) return ret;
        if((ret = example_axiocrypto_ecdh())) return ret;
		} else if (!strcmp(arg, "drbg")){
				if((ret = example_axiocrypto_drbg())) return ret;
		} else if (!strcmp(arg, "aria")){
				if((ret = example_axiocrypto_aria_gcm())) return ret;
		} else if (!strcmp(arg, "lea")){
				if((ret = example_axiocrypto_lea_gcm())) return ret;
		} else if (!strcmp(arg, "aes") && opmode == OP_MODE_NON_APPROVED){
				if((ret = example_axiocrypto_aes_gcm())) return ret;
		} else if (!strcmp(arg, "hash")){
				if((ret = example_axiocrypto_hash())) return ret;
		} else if (!strcmp(arg, "hmac")){
				if((ret = example_axiocrypto_hmac())) return ret;
		} else if (!strcmp(arg, "pbkdf")){
				if((ret = example_axiocrypto_pbkdf())) return ret;
		} else if (!strcmp(arg, "ecdsa")){
				if((ret = example_axiocrypto_ecdsa())) return ret;
		} else if (!strcmp(arg, "ecdh")){
				if((ret = example_axiocrypto_ecdh())) return ret;
		} else {
				printf("Unsupported Option\n");
				return -1;
		}

		printf("\n");
    printf("========================================\n");
    printf("AxioCrypto examples completed successfully!\n");
    printf("========================================\n\n");
    
    return 0;
}
