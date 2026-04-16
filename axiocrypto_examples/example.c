#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "axiocrypto.h"
#include "example_util.h"

// Forward declaration
#ifndef __AXIOCRYPTO_M2351__
int example_pqc(const char *arg);
#endif
int example_axiocrypto(const char *arg);

extern uint8_t activate_code[32];
extern char *user_name;

static void print_menu(void)
{
    printf("\n");
    printf("========================================\n");
    printf("AxioCrypto Shell\n");
    printf("========================================\n");
    printf("Commands:\n");
    printf("  init             - Initialize AxioCrypto\n");
    printf("  act              - Activate with code\n");
    printf("  ac <opt>         - Run AxioCrypto example\n");
    printf("                   (opt: all, drbg, aria, lea, aes, hash, hmac, pbkdf, ecdsa, ecdh)\n");
#ifndef __AXIOCRYPTO_M2351__
    printf("  pqc <opt>        - Run PQC example\n");
    printf("                   (opt: all, aimer128f, haetae2, dilithium2, sphincs128f, falcon512, kyber512, ntru768, smaug1)\n");
#endif
    printf("  ks <opt>         - Run KeyStorage example\n");
    printf("                   (opt: set, chk, del, test)\n");
    printf("  status           - Show library status\n");
    printf("  mode none/kcmvp  - Set AxioCrypto mode\n");
    printf("  log on/off       - Enable/Disable logging\n");
    printf("  int on/off       - Enable/Disable integrity check\n");
    printf("  help             - Show this menu\n");
    printf("  exit             - Exit shell\n");
    printf("========================================\n");
    printf("\n");
}

static void read_line(char *buffer, int max_len)
{
    int i = 0;
    int ch;
    
    while (i < max_len - 1) {
        ch = getchar();
        
        if (ch == '\n' || ch == '\r' || ch == EOF) {
            break;
        }
        
        // Handle backspace (0x08 or 0x7F)
        if (ch == '\b' || ch == 127) {
            if (i > 0) {
                i--;
                printf("\b \b");  // Backspace, space, backspace
                fflush(stdout);
            }
            continue;
        }
        
        // Echo the character
        putchar(ch);
        fflush(stdout);
        
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
    printf("\n");  // New line after input
}

static void cmd_init(void)
{
    CRYPTO_STATUS ret;
    
    printf("Initializing AxioCrypto...\n");
    ret = axiocrypto_init(NULL, 0);
    if (ret == CRYPTO_SUCCESS || ret == CRYPTO_ERR_ALREADY_INIT) {
        printf("Initialization successful\n");
    } else {
        printf("Initialization failed: error code %d\n", ret);
    }
}

static void cmd_activate(void)
{
    CRYPTO_STATUS ret;
    
    const char *cid = "";
    const uint8_t code[32] = {0};
    

    printf("Activating with code...\n");
    ret = axiocrypto_activate((char *)cid, (uint8_t *)code);
    if (ret == CRYPTO_SUCCESS) {
        printf("Activation successful\n");
    } else {
        printf("Activation failed: error code %d\n", ret);
    }
}

static void cmd_status(void)
{
    CRYPTO_STATUS ret;
    axiocrypto_status_t status;
    
    printf("Checking library status...\n");
    ret = axiocrypto_status(&status);
    if (ret == CRYPTO_SUCCESS) {
        printf("Target: %s\n", status.target);
        printf("UID: ");
        for (int i = 0; i < sizeof(status.uid); i++) {
            printf("%02X", status.uid[i]);
        }
        printf("\n");
        printf("Crypto Ver : %s\n", status.crypto_ver);
        printf("Library Ver: %s\n", status.library_ver);
        printf("License Type: %s\n", status.lic_type);
        printf("Activation: %s\n", status.activation_status ? "Active" : "Inactive");
        printf("Log Trace: %s\n", status.log_status ? "Enabled" : "Disabled");
        printf("Integrity Check: %s\n", status.integrity_check_status ? "Enabled" : "Disabled");
        printf("API Call Count: %d\n", (int)status.api_call_count);
        
    } else {
        printf("  Failed to get status: error code %d\n", ret);
    }
}

#ifndef __AXIOCRYPTO_M2351__
static void cmd_pqc(const char *arg)
{
		int ret = -1;

    if (arg == NULL || *arg == '\0') {
      printf("Usage: ac <all|aimer128f|haetae2|dilithium2|sphincs128f|falcon512|kyber512|ntru768|smaug1>\n");
      return;
    }
		
		printf("Running PQC example...\n");
		ret = example_pqc(arg);
		if (ret == 0) {
				printf("PQC example completed\n");
		} else {
			printf("PQC example failed(ret:%d)\n", ret);
		}
}
#endif

static void cmd_axiocrypto(const char *arg)
{
	  int ret = -1;
	
    if (arg == NULL || *arg == '\0') {
      printf("Usage: ac <all|drbg|aria|lea|aes|hash|hmac|pbkdf|ecdsa|ecdh>\n");
      return;
    }
	
    printf("Running AxioCrypto example...\n");
    ret = example_axiocrypto(arg);
    if (ret == 0) {
        printf("AxioCrypto example completed\n");
    } else {
        printf("AxioCrypto example failed(ret:%d)\n", ret);
    }
}

static void cmd_mode(operation_mode_t mode)
{
    CRYPTO_STATUS ret = CRYPTO_ERROR;
    operation_mode_t opmode = OP_MODE_NON_APPROVED;

    ret = axiocrypto_info(NULL, 0, &opmode);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_info %d\n\r", ret);
    }

    if(opmode != mode){
        printf("reboot\n\r");
        ret = axiocrypto_set_mode((uint32_t)mode);
        if(ret != CRYPTO_SUCCESS){
            printf("FAIL: axiocrypto_set_mode %d\n\r", ret);
        }
    }
    else{
        printf("Already set  %d\n\r", ret);
    }
}

static void cmd_log(int enable)
{
    CRYPTO_STATUS ret;

    if (enable) {
        printf("Enabling log...\n");
        ret = axiocrypto_enable_log();
    } else {
        printf("Disabling log...\n");
        ret = axiocrypto_disable_log();
    }
    
    if (ret == CRYPTO_SUCCESS) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
}

static void cmd_integrity(int enable)
{
    CRYPTO_STATUS ret;
    
    if (enable) {
        printf("Enabling integrity check...\n");
        ret = axiocrypto_enable_integrity_check();
    } else {
        printf("Disabling integrity check...\n");
        ret = axiocrypto_disable_integrity_check();
    }
    if (ret == CRYPTO_SUCCESS) {
        printf("Success\n");
    } else {
        printf("Failed\n");
    }
}


static void cmd_keystorage_set(ctx_handle_t handle)
{
    int ret = -1;

    uint8_t key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    uint32_t key_len = 16;

    ret = axiocrypto_allocate_slot(handle, SYM_ARIA, CTX_ATTR_PERSISTENT);
    if (ret) {
        printf("FAIL: axiocrypto_allocate_slot %d\n\r", ret);
        return;
		}

    ret = axiocrypto_sym_putkey(handle, key, key_len, 0, CTX_ATTR_PERSISTENT);
    if (ret) {
        printf("FAIL: axiocrypto_sym_putkey %d\n\r", ret);
        return;
    }
    printf("SUCCESS: cmd_keystorage_set\n");
}

static void cmd_keystorage_chk(ctx_handle_t handle)
{
    int ret = -1;
    uint16_t info = 0;

    ret = axiocrypto_get_slotinfo(handle, SYM_ARIA, &info);
    if(ret == CRYPTO_SUCCESS && (info & SLOTINFO_ATTR_DATA_EXIST) == SLOTINFO_ATTR_DATA_EXIST){
        printf("keystorage data exist\n");
        return;
    } else if(ret == CRYPTO_SUCCESS) {
        printf("keystorage data NULL\n");
    } else {
        printf("FAIL: axiocrypto_get_slotinfo %d\n\r", ret);
    }
}

static void cmd_keystorage_del(ctx_handle_t handle)
{
    int ret = -1;

    ret = axiocrypto_free_slot(handle, SYM_ARIA);
    if (ret) {
        printf("FAIL: axiocrypto_free_slot %d\n\r", ret);
        return;
    }
    printf("SUCCESS: cmd_keystorage_del\n");
}

static void cmd_keystorage_test(ctx_handle_t handle)
{
    int ret = -1;

    uint8_t aad_128[16] = {
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF,
        0xFE, 0xED, 0xFA, 0xCE, 0xDE, 0xAD, 0xBE, 0xEF
    };
    uint8_t tag[16];
		uint8_t iv[16] = {
        0xCA, 0xFE, 0xBA, 0xBE, 0xFA, 0xCE, 0xDB, 0xAD,
        0xDB, 0xAD, 0xDE, 0xCA, 0xF8, 0x88, 0xDE, 0xCA
    };

    uint8_t plain_msg[] = "Hello, AxioCrypto! This is KeyStorage test.";
    uint32_t plain_msg_len = sizeof(plain_msg) - 1;
    
    uint8_t encrypt_msg[128] = {0,};
    uint32_t encrypt_msg_len = sizeof(encrypt_msg);
    
    uint8_t decrypt_msg[128] = {0,};
    uint32_t decrypt_msg_len = sizeof(decrypt_msg);

    printf("Enc/dec test using keystorage\n");
    ret = axiocrypto_sym_enc_GCM(handle, SYM_ARIA, plain_msg, plain_msg_len, aad_128, sizeof(aad_128), tag, sizeof(tag), iv, sizeof(iv), encrypt_msg, &encrypt_msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_enc_GCM %d\n\r", ret);
        return;
    }
    ret = axiocrypto_sym_dec_GCM(handle, SYM_ARIA, encrypt_msg, encrypt_msg_len, aad_128, sizeof(aad_128), tag, sizeof(tag), iv, sizeof(iv), decrypt_msg, &decrypt_msg_len);
    if(ret != CRYPTO_SUCCESS){
        printf("FAIL: axiocrypto_sym_dec_GCM %d\n\r", ret);
        return;
    }
    printf("SUCCESS: cmd_keystorage_test\n");
}

static void cmd_keystorage(int opt)
{
    ctx_handle_t handle = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };

    if (opt == 0) {
        cmd_keystorage_set(handle);
    } else if (opt == 1) {
        cmd_keystorage_chk(handle);
    } else if (opt == 2) {
        cmd_keystorage_del(handle);
    } else if (opt == 3) {
        cmd_keystorage_test(handle);
    } else {
        printf("Unsupported keystorage option\n");
        printf("(opt: set, chk, del, test)\n");
    }
}

void example(void)
{
    char cmd_buffer[64];
    int running = 1;
    
    printf("\nWelcome to AxioCrypto Shell!\n");
    printf("Type 'help' for available commands\n");
    
    while (running) {
        printf("\naxiocrypto> ");
        read_line(cmd_buffer, sizeof(cmd_buffer));
        
        // Trim leading/trailing spaces
        char *cmd = cmd_buffer;
        while (*cmd && isspace((unsigned char)*cmd)) cmd++;
        
        if (strlen(cmd) == 0) {
            continue;
        }
        
        // Convert to lowercase for comparison
        for (char *p = cmd; *p; p++) {
            *p = tolower(*p);
        }
        
        if (strcmp(cmd, "init") == 0) {
            cmd_init();
        }
        else if (strcmp(cmd, "act") == 0) {
            cmd_activate();
        }
        else if (strncmp(cmd, "ac", 2) == 0 && (cmd[2] == '\0' || isspace((unsigned char)cmd[2]))) {
            char *arg = cmd + 2;
            while (*arg && isspace((unsigned char)*arg)) arg++;
            cmd_axiocrypto(arg);
        }
#ifndef __AXIOCRYPTO_M2351__
        else if (strncmp(cmd, "pqc", 3) == 0 && (cmd[3] == '\0' || isspace((unsigned char)cmd[3]))) {
            char *arg = cmd + 3;
            while (*arg && isspace((unsigned char)*arg)) arg++;
            cmd_pqc(arg);
        }
#endif
        else if (strcmp(cmd, "status") == 0) {
            cmd_status();
        }
				else if (strcmp(cmd, "ks set") == 0) {
            cmd_keystorage(0);
        }
        else if (strcmp(cmd, "ks chk") == 0) {
            cmd_keystorage(1);
        }
				else if (strcmp(cmd, "ks del") == 0) {
            cmd_keystorage(2);
        }
        else if (strcmp(cmd, "ks test") == 0) {
            cmd_keystorage(3);
        }
				else if (strcmp(cmd, "mode none") == 0) {
            cmd_mode(OP_MODE_NON_APPROVED);
        }
        else if (strcmp(cmd, "mode kcmvp") == 0) {
            cmd_mode(OP_MODE_APPROVED_KCMVP);
        }
        else if (strcmp(cmd, "log on") == 0) {
            cmd_log(1);
        }
        else if (strcmp(cmd, "log off") == 0) {
            cmd_log(0);
        }
        else if (strcmp(cmd, "int on") == 0) {
            cmd_integrity(1);
        }
        else if (strcmp(cmd, "int off") == 0) {
            cmd_integrity(0);
        }
        else if (strcmp(cmd, "menu") == 0 || strcmp(cmd, "help") == 0) {
            print_menu();
        }
        else if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "exit") == 0) {
            printf("Exiting AxioCrypto Shell...\n");
            running = 0;
        }
        else {
            printf("Unknown command: '%s'\n", cmd);
            printf("Type 'help' for available commands\n");
        }
    }
    
    printf("Goodbye!\n");
}
