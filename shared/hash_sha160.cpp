/* ******************************************************************** **
** @@ SHA-160 Source File
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include "stdafx.h"

#include <stdio.h>

#include "hash_sha160.h"

/* ******************************************************************** **
** @@ internal defines
** ******************************************************************** */

#define rol(value,bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

/* ******************************************************************** **
** @@ internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@ external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@ static global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@ real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ SHA160::SHA160()
** @  Copyrt : Public Domain
** @  Author :
** @  Modify : 
** @  Update :
** @  Notes  : Constructor
** ******************************************************************** */

SHA160::SHA160()
{
   Reset();
}

/* ******************************************************************** **
** @@ SHA160::~SHA160()
** @  Copyrt : 
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  : Destructor
** ******************************************************************** */

SHA160::~SHA160()
{
}

/* ******************************************************************** **
** @@ SHA160::Reset()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  : Initialize new context
** ******************************************************************** */

void SHA160::Reset()
{
   _Context.state[0] = 0x67452301;
   _Context.state[1] = 0xEFCDAB89;
   _Context.state[2] = 0x98BADCFE;
   _Context.state[3] = 0x10325476;
   _Context.state[4] = 0xC3D2E1F0;

   _Context.count[0] = 0;
   _Context.count[1] = 0;
}

/* ******************************************************************** **
** @@ SHA160::Update()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  :
** ******************************************************************** */

void SHA160::Update(const BYTE* const pBuf,DWORD dwSize)
{        
   if (!dwSize || !pBuf)
   {
      // Error !
      ASSERT(0);
      return;
   }

   if (IsBadReadPtr(pBuf,dwSize))
   {
      // Error !
      ASSERT(0);
      return;
   }

   DWORD    jj = (DWORD)((_Context.count[0] >> 3) & 63);

   if ((_Context.count[0] += dwSize << 3) < (DWORD)(dwSize << 3))
   {
      ++_Context.count[1];
   }

   _Context.count[1] += (dwSize >> 29);

   DWORD  ii = 0;

   if ((jj + dwSize) > 63)
   {
      memcpy(&_Context.buffer[jj],pBuf,(ii = (DWORD)(64 - jj)));

      Transform(_Context.buffer);

      for ( ; ii + 63 < dwSize; ii += 64)
      {
         Transform(&pBuf[ii]);
      }

      jj = 0;
   }
   else
   {
      ii = 0;
   }

   memcpy(&_Context.buffer[jj],&pBuf[ii],dwSize - ii);
}

/* ******************************************************************** **
** @@ SHA160::Finalize()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  : Add padding and return the message digest
** ******************************************************************** */

void SHA160::Finalize()
{
   BYTE     finalcount[8];

   // Endian independent
   for (int ii = 0; ii < 8; ii++)
   {
      finalcount[ii] = (BYTE)((_Context.count[(ii >= 4 ? 0 : 1)] >> ((3 - (ii & 3)) * 8) ) & 255);
   }

   Update((BYTE*)"\200",1);

   while ((_Context.count[0] & 504) != 448)
   {
      Update((BYTE*)"\0",1);
   }

   // Should cause a Transform()
   Update(finalcount,8);

   for (int jj = 0; jj < SHA160_DIGEST_SIZE; ++jj)
   {
      _pDigest[jj] = (BYTE)((_Context.state[jj >> 2] >> ((3 - (jj & 3)) * 8)) & 0xFF);
   }

   for (int kk = 0; kk < SHA160_DIGEST_SIZE; ++kk)
   {
      sprintf(&_pszSignature[kk * 2],"%02X",_pDigest[kk]);
   }

   _pszSignature[SHA160_SIGNATURE_SIZE - 1] = 0; // Ensure ASCIIZ
}

/* ******************************************************************** **
** @@ SHA160::Burn()
** @  Copyrt : 
** @  Author :
** @  Modify : 
** @  Update :
** @  Notes  : In case it's sensitive
** ******************************************************************** */

void SHA160::Burn()
{
   memset(&_Context,0xFF,sizeof(_Context)); 
}

/* ******************************************************************** **
** @@ SHA160::Digest()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

const BYTE* const SHA160::Digest()
{
   return _pDigest;
}

/* ******************************************************************** **
** @@ SHA160::Digest()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */
    
const char* const SHA160::Signature()
{
   return _pszSignature;
}

/* ******************************************************************** **
** @@ SHA160::Transform()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  : Hash a single 512-bit block. This is the core of the algorithm
** ******************************************************************** */

void SHA160::Transform(const BYTE buffer[64])
{
   DWORD    a;
   DWORD    b;
   DWORD    c;
   DWORD    d;
   DWORD    e;

   memcpy(_block,buffer,64);

   // Copy context to working vars
   a = _Context.state[0];
   b = _Context.state[1];
   c = _Context.state[2];
   d = _Context.state[3];
   e = _Context.state[4];

   // 4 rounds of 20 operations each. Loop unrolled
   R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);
   R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);
   R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
   R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);

   R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);

   R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);
   R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);
   R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);
   R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);
   R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);

   R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);
   R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);
   R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);
   R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);
   R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);

   R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);
   R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);
   R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);
   R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);
   R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);

   // Add the working vars back into context.state[]
   _Context.state[0] += a;
   _Context.state[1] += b;
   _Context.state[2] += c;
   _Context.state[3] += d;
   _Context.state[4] += e;

   // Wipe variables
   a = 0;
   b = 0;
   c = 0;
   d = 0;
   e = 0;
}

/* ******************************************************************** **
** @@ SHA160::blk0()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  : blk0() and blk() perform the initial expand.
** @  Notes  : I got the idea of expanding during the round function from SSLeay 
** ******************************************************************** */

DWORD SHA160::blk0(DWORD ii)
{
   return (_block[ii] = (rol(_block[ii],24) & 0xFF00FF00) | (rol(_block[ii],8) & 0x00FF00FF));
}

/* ******************************************************************** **
** @@ SHA160::blk()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  : blk0() and blk() perform the initial expand.
** @  Notes  : I got the idea of expanding during the round function from SSLeay 
** ******************************************************************** */

DWORD SHA160::blk(DWORD ii)
{
   return (_block[ii & 15] = rol(_block[(ii + 13) & 15] ^ _block[(ii + 8) & 15] ^ _block[(ii + 2) & 15] ^ _block[ii & 15],1));
}

/* ******************************************************************** **
** @@ SHA160::R0()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  :
** ******************************************************************** */

void SHA160::R0(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i)
{
  z += ((w & (x ^ y)) ^ y) + blk0(i) + 0x5A827999 + rol(v,5); 
  w = rol(w,30);
}

/* ******************************************************************** **
** @@ SHA160::R1()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  :
** ******************************************************************** */

void SHA160::R1(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i)
{
  z += ((w & (x ^ y)) ^ y) + blk(i) + 0x5A827999 + rol(v,5); 
  w = rol(w,30);
}

/* ******************************************************************** **
** @@ SHA160::R2()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  :
** ******************************************************************** */

void SHA160::R2(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i)
{
  z += (w ^ x ^ y) + blk(i) + 0x6ED9EBA1 + rol(v,5); 
  w = rol(w,30);
}

/* ******************************************************************** **
** @@ SHA160::R3()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  :
** ******************************************************************** */

void SHA160::R3(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i)
{
  z += (((w | x) & y) | (w & x)) + blk(i) + 0x8F1BBCDC + rol(v,5); 
  w = rol(w,30);
}

/* ******************************************************************** **
** @@ SHA160::R4()
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Notes  :
** ******************************************************************** */

void SHA160::R4(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i)
{
  z += (w ^ x ^ y) + blk(i) + 0xCA62C1D6 + rol(v,5); 
  w = rol(w,30);
}

/* ******************************************************************** **
** @@                   End of File
** ******************************************************************** */
