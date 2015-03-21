#include <stdio.h>
#include <Windows.h>

const unsigned char S_box[] = { 0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15, 0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF, 0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8, 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, 0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, 0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08, 0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, 0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, 0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16 };
const unsigned char matrix[16] = {
    1, 2, 0, 0,
    0, 1, 2, 0,
    0, 0, 1, 2,
    2, 0, 0, 1
},
gmul[3][0x100] = {
        { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF },
        { 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C, 0x8E, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9A, 0x9C, 0x9E, 0xA0, 0xA2, 0xA4, 0xA6, 0xA8, 0xAA, 0xAC, 0xAE, 0xB0, 0xB2, 0xB4, 0xB6, 0xB8, 0xBA, 0xBC, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE, 0xD0, 0xD2, 0xD4, 0xD6, 0xD8, 0xDA, 0xDC, 0xDE, 0xE0, 0xE2, 0xE4, 0xE6, 0xE8, 0xEA, 0xEC, 0xEE, 0xF0, 0xF2, 0xF4, 0xF6, 0xF8, 0xFA, 0xFC, 0xFE, 0x1B, 0x19, 0x1F, 0x1D, 0x13, 0x11, 0x17, 0x15, 0x0B, 0x09, 0x0F, 0x0D, 0x03, 0x01, 0x07, 0x05, 0x3B, 0x39, 0x3F, 0x3D, 0x33, 0x31, 0x37, 0x35, 0x2B, 0x29, 0x2F, 0x2D, 0x23, 0x21, 0x27, 0x25, 0x5B, 0x59, 0x5F, 0x5D, 0x53, 0x51, 0x57, 0x55, 0x4B, 0x49, 0x4F, 0x4D, 0x43, 0x41, 0x47, 0x45, 0x7B, 0x79, 0x7F, 0x7D, 0x73, 0x71, 0x77, 0x75, 0x6B, 0x69, 0x6F, 0x6D, 0x63, 0x61, 0x67, 0x65, 0x9B, 0x99, 0x9F, 0x9D, 0x93, 0x91, 0x97, 0x95, 0x8B, 0x89, 0x8F, 0x8D, 0x83, 0x81, 0x87, 0x85, 0xBB, 0xB9, 0xBF, 0xBD, 0xB3, 0xB1, 0xB7, 0xB5, 0xAB, 0xA9, 0xAF, 0xAD, 0xA3, 0xA1, 0xA7, 0xA5, 0xDB, 0xD9, 0xDF, 0xDD, 0xD3, 0xD1, 0xD7, 0xD5, 0xCB, 0xC9, 0xCF, 0xCD, 0xC3, 0xC1, 0xC7, 0xC5, 0xFB, 0xF9, 0xFF, 0xFD, 0xF3, 0xF1, 0xF7, 0xF5, 0xEB, 0xE9, 0xEF, 0xED, 0xE3, 0xE1, 0xE7, 0xE5 },
        { 0x00, 0x03, 0x06, 0x05, 0x0C, 0x0F, 0x0A, 0x09, 0x18, 0x1B, 0x1E, 0x1D, 0x14, 0x17, 0x12, 0x11, 0x30, 0x33, 0x36, 0x35, 0x3C, 0x3F, 0x3A, 0x39, 0x28, 0x2B, 0x2E, 0x2D, 0x24, 0x27, 0x22, 0x21, 0x60, 0x63, 0x66, 0x65, 0x6C, 0x6F, 0x6A, 0x69, 0x78, 0x7B, 0x7E, 0x7D, 0x74, 0x77, 0x72, 0x71, 0x50, 0x53, 0x56, 0x55, 0x5C, 0x5F, 0x5A, 0x59, 0x48, 0x4B, 0x4E, 0x4D, 0x44, 0x47, 0x42, 0x41, 0xC0, 0xC3, 0xC6, 0xC5, 0xCC, 0xCF, 0xCA, 0xC9, 0xD8, 0xDB, 0xDE, 0xDD, 0xD4, 0xD7, 0xD2, 0xD1, 0xF0, 0xF3, 0xF6, 0xF5, 0xFC, 0xFF, 0xFA, 0xF9, 0xE8, 0xEB, 0xEE, 0xED, 0xE4, 0xE7, 0xE2, 0xE1, 0xA0, 0xA3, 0xA6, 0xA5, 0xAC, 0xAF, 0xAA, 0xA9, 0xB8, 0xBB, 0xBE, 0xBD, 0xB4, 0xB7, 0xB2, 0xB1, 0x90, 0x93, 0x96, 0x95, 0x9C, 0x9F, 0x9A, 0x99, 0x88, 0x8B, 0x8E, 0x8D, 0x84, 0x87, 0x82, 0x81, 0x9B, 0x98, 0x9D, 0x9E, 0x97, 0x94, 0x91, 0x92, 0x83, 0x80, 0x85, 0x86, 0x8F, 0x8C, 0x89, 0x8A, 0xAB, 0xA8, 0xAD, 0xAE, 0xA7, 0xA4, 0xA1, 0xA2, 0xB3, 0xB0, 0xB5, 0xB6, 0xBF, 0xBC, 0xB9, 0xBA, 0xFB, 0xF8, 0xFD, 0xFE, 0xF7, 0xF4, 0xF1, 0xF2, 0xE3, 0xE0, 0xE5, 0xE6, 0xEF, 0xEC, 0xE9, 0xEA, 0xCB, 0xC8, 0xCD, 0xCE, 0xC7, 0xC4, 0xC1, 0xC2, 0xD3, 0xD0, 0xD5, 0xD6, 0xDF, 0xDC, 0xD9, 0xDA, 0x5B, 0x58, 0x5D, 0x5E, 0x57, 0x54, 0x51, 0x52, 0x43, 0x40, 0x45, 0x46, 0x4F, 0x4C, 0x49, 0x4A, 0x6B, 0x68, 0x6D, 0x6E, 0x67, 0x64, 0x61, 0x62, 0x73, 0x70, 0x75, 0x76, 0x7F, 0x7C, 0x79, 0x7A, 0x3B, 0x38, 0x3D, 0x3E, 0x37, 0x34, 0x31, 0x32, 0x23, 0x20, 0x25, 0x26, 0x2F, 0x2C, 0x29, 0x2A, 0x0B, 0x08, 0x0D, 0x0E, 0x07, 0x04, 0x01, 0x02, 0x13, 0x10, 0x15, 0x16, 0x1F, 0x1C, 0x19, 0x1A }
};

void key_schedule(unsigned char key[16], unsigned char round_keys[11][16])
{
    #define DW(t) (*(unsigned int*)(t))
    #define ROR(a, n) ((a >> n) | ((a) << (32 - n)))
    #define ROT(a) (ROR((a), 8))

    unsigned int d;
    unsigned char state[16] = { 0 };
    const unsigned char rcon[] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39, 0x72, 0xE4, 0xD3, 0xBD, 0x61, 0xC2, 0x9F, 0x25, 0x4A, 0x94, 0x33, 0x66, 0xCC, 0x83, 0x1D, 0x3A, 0x74, 0xE8, 0xCB, 0x8D };

    /// Key schedule -- Generate one subkey for each round
    /// http://www.formaestudio.com/rijndaelinspector/archivos/Rijndael_Animation_v4_eng.swf

    // First round-key is the actual key
    memcpy(&round_keys[0][0], key, 16);
    d = DW(&round_keys[0][12]);
    for (size_t i = 1; i < 11; ++i)
    {
        // Rotate `d` 8 bits to the right
        d = ROT(d);

        // Takes every bytes of `d` & substitute them using `S_box`
        unsigned char a1, a2, a3, a4;
        // Do not forget to xor this byte with `rcon[i]`
        a1 = S_box[(d >> 0) & 0xff] ^ rcon[i]; // a1 is the LSB
        a2 = S_box[(d >> 8) & 0xff];
        a3 = S_box[(d >> 16) & 0xff];
        a4 = S_box[(d >> 24) & 0xff];

        d = (a1 << 0) | (a2 << 8) | (a3 << 16) | (a4 << 24);

        // Now we can generate the current roundkey using the previous one
        for (size_t j = 0; j < 4; j++)
        {
            d ^= DW(&(round_keys[i - 1][j * 4]));
            *(unsigned int*)(&(round_keys[i][j * 4])) = d;
        }
    }
}

void ShiftRows(unsigned char out[16])
{
    unsigned char tmp1, tmp2;

    // 8-bits left rotation of the second line
    tmp1 = out[1];
    out[1] = out[5];
    out[5] = out[9];
    out[9] = out[13];
    out[13] = tmp1;

    // 16-bits left rotation of the third line
    tmp1 = out[2];
    tmp2 = out[6];
    out[2] = out[10];
    out[6] = out[14];
    out[10] = tmp1;
    out[14] = tmp2;

    // 24-bits left rotation of the last line
    tmp1 = out[3];
    out[3] = out[15];
    out[15] = out[11];
    out[11] = out[7];
    out[7] = tmp1;
}

int main()
{
    unsigned char key[16] = "0vercl0k@doare-e";
    unsigned char plain_block[16] = "whatdup folks???";
    unsigned char round_keys[11][16] = { 0 };

    /// 10 -> we have 10 rounds
    /// 16 -> we have 16 bytes of round keys
    /// 0x100 -> we have to be able to encrypt every plain-text input byte [0-0xff]
    unsigned char Tboxes[10][16][0x100] = { 0 };

    key_schedule(key, round_keys);

    /// Remember we have 10 rounds & we want to combine AddRoundKey & SubBytes
    /// which is really simple.
    /// These so-called T-boxes are defined as follows:
    /// Tri(x) = S[x ^ ShiftRows(rk)[i]] ; r being the round number ([0-8]), x being the byte of plaintextn rk the roundkey & i the index ([0-15])
    printf("#pragma once\n");
    printf("// Table for key='%.16s'\n", key);
    printf("const unsigned char Tboxes[10][16][0x100] = \n{\n");
    for (size_t r = 0; r < 10; ++r)
    {
        printf("  {\n");
 
        ShiftRows(round_keys[r]);

        for (size_t i = 0; i < 16; ++i)
        {
            printf("    {\n      ");
            for (size_t x = 0; x < 0x100; ++x)
            {
                if (x != 0 && (x % 16) == 0)
                    printf("\n      ");

                Tboxes[r][i][x] = S_box[x ^ round_keys[r][i]];
                /// We need to include the bytes from the roundkey 10 to replace that:
                ///  ShiftRows(out);
                ///  ShiftRows(round_keys[9]);
                ///  AddRoundKey(round_keys[9], out);
                ///  SubBytes(out);
                ///  AddRoundKey(round_keys[10], out);
                ///
                /// By
                /// ShiftRows(out);
                /// for (size_t j = 0; j < 16; ++j)
                ///     out[j] = Tboxes[9][j][out[j]];
                if (r == 9)
                    Tboxes[r][i][x] ^= round_keys[10][i];

                printf("0x%.2x", Tboxes[r][i][x]);
                if ((x + 1) < 0x100)
                    printf(", ");
            }
            printf("\n    }");
            if ((i + 1) < 16)
                printf(",");

            printf("\n");
        }
        printf("  }");
        if ((r + 1) < 10)
            printf(",");
        printf("\n");
    }
    printf("};\n\n");

    /// Here we are computing Tyi tables ; this is to transform MixColumn in some table lookups
    /// MixColumns is basically doing that:
    /// unsigned char a = out[i * 4 + 0];
    /// out[i * 4 + 0] = gmul[matrix[0]][a] ^ gmul[matrix[1]][b] ^ gmul[matrix[2]][c] ^ gmul[matrix[3]][d];
    /// ...
    ///
    /// Basically we can turn that into 4 tables:
    /// Ty0(x) = [gmul[matrix[0]][x], gmul[matrix[4]][x], gmul[matrix[8]][x], gmul[matrix[12]][x]] ^ T
    /// Ty1(x) = 
    /// Ty2(x) = 
    /// Ty3(x) = 
    /// out[i * 4 + 0] = Ty0(a) ^ Ty1(b) ^ Ty2(c) ^ Ty3(d)
    ///                = 

    typedef union
    {
        unsigned char b[4];
        unsigned int i;
    } magic_int;

    /// 4 -> four rows MC
    /// 0x100 -> for every char
    unsigned int Ty[4][0x100] = { 0 };
    printf("const unsigned int Ty[4][16][0x100] =\n{\n");
    for (size_t i = 0; i < 4; ++i)
    {
        printf("  {\n    ");
        for (size_t j = 0; j < 0x100; ++j)
        {
            if (j != 0 && (j % 16) == 0)
                printf("\n    ");

            magic_int mi;

            mi.b[0] = gmul[matrix[i + 0]][j];
            mi.b[1] = gmul[matrix[i + 4]][j];
            mi.b[2] = gmul[matrix[i + 8]][j];
            mi.b[3] = gmul[matrix[i + 12]][j];

            Ty[i][j] = mi.i;

            printf("0x%.8x", Ty[i][j]);
            if ((j + 1) < 0x100)
                printf(", ");
        }

        printf("\n  }");
        if ((i + 1) < 4)
            printf(",");
        printf("\n");
    }
    printf("};\n");

    /// Xor Tables
    /// Basically takes two nibbles in input & generate a nibble in output (x^y)
    unsigned char Xor[0x10][0x10] = { 0 };
    printf("const unsigned char Xor[0x10][0x10] =\n{\n");
    for (size_t i = 0; i < 0x10; ++i)
    {
        printf("  {\n    ");

        for (size_t j = 0; j < 0x10; ++j)
        {
            if (j != 0 && (j % 8) == 0)
                printf("\n    ");

            Xor[i][j] = i ^ j;
            printf("0x%.1x", Xor[i][j]);
            if ((j + 1) < 0x10)
                printf(", ");
        }

        printf("\n  }");
        if ((i + 1) < 0x10)
            printf(",");
        printf("\n");
    }
    printf("};\n");

    /// Tyboxes
    /// It's basically Tybox(Tboxes(x))
    unsigned int Tyboxes[9][16][0x100] = { 0 };
    printf("const unsigned int Tyboxes[9][16][0x100] =\n{\n");
    for (size_t r = 0; r < 9; ++r)
    {
        printf("  {\n");

        // ShiftRows(round_keys[r]);

        for (size_t i = 0; i < 16; ++i)
        {
            printf("    {\n      ");
            for (size_t x = 0; x < 0x100; ++x)
            {
                if (x != 0 && (x % 16) == 0)
                    printf("\n      ");

                unsigned char c = S_box[x ^ round_keys[r][i]];
                Tyboxes[r][i][x] = Ty[i % 4][c];

                printf("0x%.8x", Tyboxes[r][i][x]);
                if ((x + 1) < 0x100)
                    printf(", ");
            }

            printf("\n    }");
            if ((i + 1) < 16)
                printf(",");

            printf("\n");
        }
        printf("  }");
        if ((r + 1) < 10)
            printf(",");
        printf("\n");
    }
    printf("};\n");

    printf("const unsigned char Tboxes_[16][0x100] = \n{\n");
    for (size_t i = 0; i < 16; ++i)
    {
        printf("  {\n    ");
        for (size_t x = 0; x < 0x100; ++x)
        {
            if (x != 0 && (x % 16) == 0)
                printf("\n    ");

            Tboxes[9][i][x] = S_box[x ^ round_keys[9][i]] ^ round_keys[10][i];
            printf("0x%.2x", Tboxes[9][i][x]);
            if ((x + 1) < 0x100)
                printf(", ");
        }
        printf("\n  }");
        if ((i + 1) < 16)
            printf(",");

        printf("\n");
    }

    printf("};\n\n");
    return EXIT_SUCCESS;
}