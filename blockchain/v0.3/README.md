# 0x03. Blockchain - Transactions
* The UTXO Model
## General
How to build a transaction
What is a transaction input
What is a transaction output
Why to sign a transaction input
How to compute the balance of given wallet
What is a coinbase transaction and why it is used
How to ensure immutability of a transaction
What is the difference between the UTXO and the Account-based transaction models
## Requirements
# General
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra, -pedantic and the linker flags -lssl and -lcrypto
* Your library libhblk_crypto.a, located in the crypto folder will be built and linked during correction
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* The prototypes of all your functions should be included in your header file called blockchain/v0.3/blockchain.h
* All your header files should be include guarded

# More Info
## Prerequisites
* Create the folder blockchain/v0.3/ and copy the following files in it:

blockchain/v0.2/blockchain_create.c
blockchain/v0.2/blockchain_deserialize.c
blockchain/v0.2/blockchain_destroy.c
blockchain/v0.2/blockchain.h
blockchain/v0.2/blockchain_serialize.c
blockchain/v0.2/block_create.c
blockchain/v0.2/block_destroy.c
blockchain/v0.2/block_hash.c
blockchain/v0.2/block_is_valid.c
* Modify your code so when a Blockchain is serialized, the version stored is 0.3

## Data structures
Please refer to the concept page attached to this project. Don’t forget to update the Blockchain and Block data structures.

## Additional information
* Unless specified otherwise, you are allowed to use the C standard library
* You are free to use any data structure that suits you as long as their purpose is well defined
* You are free to print any information on stderr, this stream will be discarded during correction. Since you are going to use these utility functions in your Blockchain project, you are free to manage errors as you wish.
* At the end of this project, the structure of your repository should look like this (you may have additional files):
```
holbertonschool-blockchain
├── blockchain
│   ├── v0.1/
│   ├── v0.2/
│   └── v0.3
│       ├── blockchain_create.c
│       ├── blockchain_deserialize.c
│       ├── blockchain_destroy.c
│       ├── blockchain_difficulty.c
│       ├── blockchain.h
│       ├── blockchain_serialize.c
│       ├── block_create.c
│       ├── block_destroy.c
│       ├── block_hash.c
│       ├── block_is_valid.c
│       ├── block_mine.c
│       ├── hash_matches_difficulty.c
│       ├── libhblk_blockchain_v0.3.a
│       ├── Makefile
│       ├── provided
│       │   ├── _blockchain_print.c
│       │   ├── _endianness.c
│       │   ├── endianness.h
│       │   ├── _genesis.c
│       │   ├── _print_hex_buffer.c
│       │   └── _transaction_print.c
│       ├── test
│       │   ├── blockchain_create-main.c
│       │   ├── blockchain_deserialize-main.c
│       │   ├── blockchain_destroy-main.c
│       │   ├── blockchain_difficulty-main.c
│       │   ├── blockchain_serialize-main.c
│       │   ├── block_create-main.c
│       │   ├── block_destroy-main.c
│       │   ├── block_hash-main.c
│       │   ├── block_is_valid-main.c
│       │   ├── block_mine-main.c
│       │   └── hash_matches_difficulty-main.c
│       └── transaction
│           ├── coinbase_create.c
│           ├── coinbase_is_valid.c
│           ├── test
│           │   ├── coinbase_create-main.c
│           │   ├── coinbase_is_valid-main.c
│           │   ├── transaction_create-main.c
│           │   ├── transaction_destroy-main.c
│           │   ├── transaction_hash-main.c
│           │   ├── transaction_is_valid-main.c
│           │   ├── tx_in_create-main.c
│           │   ├── tx_in_sign-main.c
│           │   ├── tx_out_create-main.c
│           │   ├── unspent_tx_out_create-main.c
│           │   └── update_unspent-main.c
│           ├── transaction_create.c
│           ├── transaction_destroy.c
│           ├── transaction.h
│           ├── transaction_hash.c
│           ├── transaction_is_valid.c
│           ├── tx_in_create.c
│           ├── tx_in_sign.c
│           ├── tx_out_create.c
│           ├── unspent_tx_out_create.c
│           └── update_unspent.c
├── crypto/
└── README.md```