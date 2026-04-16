/**
 * @file example_util.c
 * @brief Utility functions for AxioCrypto examples
 */

#include <stdio.h>
#include <string.h>
#include "example_util.h"
#if defined(__AXIOCRYPTO_M2354__) || defined(__AXIOCRYPTO_M2351__)
#else
#include <stm32h5xx_hal.h>
#endif

void print_hex(const char *label, const uint8_t *data, uint32_t len)
{
    printf("%s", label);
    for (uint32_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
        if ((i + 1) % 16 == 0 && (i + 1) < len)
            printf("\n%*s", (int)strlen(label), "");
    }
    printf("\n");
}

volatile uint32_t g_ms_ticks = 0;

#if defined(__AXIOCRYPTO_M2354__) || defined(__AXIOCRYPTO_M2351__)
void SysTick_Handler(void)
{
    g_ms_ticks++;
}
#endif

void init_ms_ticks(void)
{
#if defined(__AXIOCRYPTO_M2354__) || defined(__AXIOCRYPTO_M2351__)
    g_ms_ticks = 0;
#else
    g_ms_ticks = HAL_GetTick();
#endif
}

uint32_t get_ms_ticks(void)
{
#if defined(__AXIOCRYPTO_M2354__) || defined(__AXIOCRYPTO_M2351__)
    return g_ms_ticks;
#else
    return HAL_GetTick() - g_ms_ticks;
#endif
}
