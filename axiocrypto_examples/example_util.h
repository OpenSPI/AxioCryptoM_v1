/**
 * @file example_util.h
 * @brief Utility functions for AxioCrypto examples
 */

#ifndef EXAMPLE_UTIL_H
#define EXAMPLE_UTIL_H

#include <stdint.h>
#include <inttypes.h>
#include "axiocrypto_defines.h"

/**
 * @brief Print data in hexadecimal format
 * @param label Label to print before the data
 * @param data Pointer to data buffer
 * @param len Length of data in bytes
 */
void print_hex(const char *label, const uint8_t *data, uint32_t len);

extern volatile uint32_t g_ms_ticks;
void init_ms_ticks(void);
uint32_t get_ms_ticks(void);

#endif /* EXAMPLE_UTIL_H */
