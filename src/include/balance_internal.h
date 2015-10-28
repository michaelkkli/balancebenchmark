#ifndef BALANCE_INTERNAL_H
#define BALANCE_INTERNAL_H
/* Guard macros placed before pragma once to allow multiple-include
 * optimization if pragma once is unsupported.
 * https://gcc.gnu.org/onlinedocs/cppinternals/Guard-Macros.html
 */
#pragma once

#include <stdint.h>
#include <string.h>

void _bal_mrg8 (uint64_t * ptr, size_t num);
void _bal_pja_invnorm( double * p, size_t num);

#endif /* BALANCE_INTERNAL_H */
