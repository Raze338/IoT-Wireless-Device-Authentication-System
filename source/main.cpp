#include "aes128_ecb.h"  // Your AES implementation header
#include "md5.h"         // Include an MD5 hashing library
#include "sha256.h"      // Include a SHA-256 hashing library
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <fcntl.h>     // For O_RDONLY
#include <unistd.h>    // For read() and close()
#include <sys/types.h> // For ssize_t
#include <random>
#include <algorithm>
#include "MicroBit.h"

MicroBit uBit;

// Custom key generation function
void generate_aes_key(const BYTE secret[], const BYTE salt[], BYTE aes_key[]) {
    BYTE K1[16];       // MD5 of secret
    BYTE K2[16];       // MD5 of salt
    BYTE K3[32];       // Concatenation of K1 and K2
    BYTE K4[32];       // SHA-256 of salt
    BYTE DPK[32];      // Final XNOR result
	
	MD5_CTX salt_ctx, secret_ctx;

    md5_init(&secret_ctx);
    md5_update(&secret_ctx, secret, strlen(reinterpret_cast<const char*>(secret)));  // Length excludes null terminator
    md5_final(&secret_ctx, K1);
	
    md5_init(&salt_ctx);
    md5_update(&salt_ctx, salt, strlen(reinterpret_cast<const char*>(salt)));  // Length excludes null terminator
    md5_final(&salt_ctx, K2);

    memcpy(K3, K1, 16); // K3[0-16] = K1[0-16]
    memcpy(K3 + 16, K2, 16); // K3[16-32] = k2[0-16]

	SHA256_CTX ctx;
	
    sha256_init(&ctx);
	sha256_update(&ctx, salt, strlen(reinterpret_cast<const char*>(salt)));
	sha256_final(&ctx, K4);

    for (int i = 0; i < 32; i++) {
        DPK[i] = ~(K3[i] ^ K4[i]);
    }

    memcpy(aes_key, DPK, 16);
}

void generate_salt(BYTE salt[]) {
	std::random_device rd;
	std::generate(salt, salt + 16, [&rd]() { return rd(); });
}	

void display_salt(const BYTE salt[]) {
	std::cout << "Generated Salt: ";
	for (std::size_t i = 0; i < 16; ++i) {
		std::cout << /* std::hex << static_cast<int>( */ salt[i];
	}
	std::printf("%ld", std::strlen(reinterpret_cast<const char*>(salt)));
}

// Main encryption and decryption example
int main() {
	uBit.init();
    BYTE secret[16] = "secret1secret21";
    BYTE salt[16];
    generate_salt(salt);
    BYTE aes_key[16];
    
    aes128_ctx ctx;
    aes128_init_ctx(&ctx);

    // Generate the AES key
    generate_aes_key(secret, salt, aes_key);
    aes128_set_key(&ctx, aes_key);

    // Sample plaintext block
    BYTE command[16] = "";
    BYTE ciphertext[16];
    BYTE decryptedtext[16];

    // Encrypt
    memcpy(ciphertext, command, 16);
    aes128_ecb_encrypt(&ctx, ciphertext);

    // Decrypt
    memcpy(decryptedtext, ciphertext, 16);
    aes128_ecb_decrypt(&ctx, decryptedtext);

    // Output results
	ManagedString comm = reinterpret_cast<const char*>(command);
    uBit.serial.printf("Command: ");
    uBit.serial.send(comm);
    uBit.serial.printf("\r\nCiphertext: ");
    for (int i = 0; i < 16; i++) uBit.serial.printf("%02x", ciphertext[i]);
    uBit.serial.printf("\r\nDecrypted text: %s\n", decryptedtext);

    release_fiber();


}

