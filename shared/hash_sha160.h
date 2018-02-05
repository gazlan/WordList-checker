/* ******************************************************************** **
** @@ SHA-160 Header File
** @  Copyrt : Public Domain
** @  Author : Steve Reid <steve@edmweb.com>
** @  Modify : 
** @  Update :
** @  Dscr   :
** ******************************************************************** */

#ifndef _SHA160_HPP_
#define _SHA160_HPP_

#if _MSC_VER > 1000
#pragma once
#endif

#define  SHA160_DIGEST_SIZE            (sizeof(DWORD) * 5)
#define  SHA160_SIGNATURE_SIZE         (SHA160_DIGEST_SIZE * 2 + 1)

/* ******************************************************************** **
** @@ SHA-160
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Dscr   :
** @  Notes  :
** ******************************************************************** */

class SHA160
{
   private:

      struct SHA160_CONTEXT
      {
         DWORD    state[5];
         DWORD    count[2];
         BYTE     buffer[64];
      };

      SHA160_CONTEXT    _Context;
      DWORD             _block[16];
      BYTE              _pDigest     [SHA160_DIGEST_SIZE];
      char              _pszSignature[SHA160_SIGNATURE_SIZE];

   public:

               SHA160();
      virtual ~SHA160();

      void                 Reset();
      void                 Update(const BYTE* const data,DWORD dwSize);
      void                 Finalize();
      const BYTE* const    Digest();
      const char* const    Signature();
      void                 Burn();

   private:

      void  Transform(const BYTE buffer[64]);

      DWORD blk0(DWORD i);
      DWORD blk (DWORD i);

      void R0(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i);
      void R1(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i);
      void R2(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i);
      void R3(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i);
      void R4(DWORD v,DWORD& w,DWORD x,DWORD y,DWORD& z,DWORD i);
};

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */

#endif
