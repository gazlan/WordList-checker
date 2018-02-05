#ifndef _MURMUR_HASH_3_HPP_
#define _MURMUR_HASH_3_HPP_

const DWORD    MM3_DEFAULT_HASH_SEED = 0x12345678;

DWORD __fastcall MurmurHash3_x86_32(const void* const pBuf,DWORD dwSize,DWORD dwSeed);

void  MurmurHash3_x86_128(const void* const pBuf,DWORD dwSize,DWORD dwSeed,void* pOut);

#endif

/* ******************************************************************** **
** @@                   End of File
** ******************************************************************** */
