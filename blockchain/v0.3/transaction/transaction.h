#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "blockchain.h"

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);

#endif /* _TRANSACTION_H_ */
