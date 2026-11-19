# Simple Encryption Using XOR

**COMP 211 – Checkoff 3** · Luana Siucho · November 2026
Topic: *Applications of Bitwise Operators – Simple Encryption Using XOR*

## Overview

In COMP 211 we used the bitwise XOR operator (`^`) to manipulate bits. For this project I looked at how that same operator can be used to encrypt a message, and at why a simple XOR cipher is easy to break.

XOR outputs `1` when two bits are different and `0` when they are the same:

| a | b | a ^ b |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

Two properties make encryption possible:

- `x ^ 0 == x`: XOR with 0 changes nothing.
- `x ^ x == 0`: anything XORed with itself cancels out.

Together they give:

```
(message ^ key) ^ key == message
```

XORing with the same key twice undoes itself. Encryption and decryption are the exact same operation.

## What I Explored

1. **How XOR encryption works.** I worked through a single byte by hand: `'H'` (0x48) XOR key 0x5A = 0x12, and XORing again returns `'H'`.
2. **Writing it in C.** I wrote a program that encrypts `"HELLO"` with the repeating key `"KEY"`, prints the encrypted bytes, and then decrypts it with the same function.
3. **Why it's insecure.** I looked at how an attacker can recover the key, and at the conditions that would make XOR encryption secure.

## Key Discoveries

### 1. A `00` byte showed up in my output

Running the program printed:

```
03 00 15 07 0A
HELLO
```

The second byte is `00`. The second letter of HELLO is `E`, and the second letter of the key is also `E`, so `E ^ E = 0`. The ciphertext leaks information: a `00` byte tells an attacker that the message and the key match at that position.

It also explains a C detail in the code. The program saves the message length *before* encrypting, because `strlen` stops at the first `0` byte and would think the encrypted message is only 1 character long.

### 2. Guessing part of the message reveals the key

Since `ciphertext = message ^ key`, it follows that `key = ciphertext ^ message`. If an attacker guesses the message starts with `"HEL"`:

```
0x03 ^ 'H' = 'K'
0x00 ^ 'E' = 'E'
0x15 ^ 'L' = 'Y'
```

Three guessed letters reveal the entire key, `"KEY"`. I verified this by running it in C.

### 3. The key is everything

XOR itself isn't the weak part. The key is. XOR encryption is only secure (a **one-time pad**) if the key is:

- truly random
- at least as long as the message
- never reused
- kept secret

Modern encryption, such as ChaCha20, still uses XOR as its final step. The difference is that it generates a long random key that never repeats.

**Takeaway:** XOR is great for encryption, but you have to be very careful with your key.

## Running the Code

Requires a C compiler (e.g. `gcc`).

```bash
cd code
gcc xor_cipher.c -o xor_cipher
./xor_cipher
```

Expected output:

```
03 00 15 07 0A
HELLO
```

## Repository Contents

```
xor-encryption/
├── code/
│   └── xor_cipher.c        # encrypt/decrypt demo
├── README.md
└── xor-presentation.pdf    # presentation slides
```

## Resources

- AI learning conversation: [https://claude.ai/share/17083ad3-916a-479b-938b-2eb869b2da13](url)
- [XOR cipher – Wikipedia](https://en.wikipedia.org/wiki/XOR_cipher)
- [One-time pad – Wikipedia](https://en.wikipedia.org/wiki/One-time_pad)
- [Bitwise operation – Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)
