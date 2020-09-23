#include <stdio.h>
#include <string.h>
#include "bandb.h"

void getbytes( unsigned char dest[], int bytes, void *src, int reverse) {
  int i;
  unsigned char* temp = src;
  //int sizeDiff = sizeof(temp) - bytes;
//  printf("sizeOf input : %lu\n", strlen(temp));
  //printf("SizeDiff: %d\n", sizeDiff);

  //printf("%lu", sizeof(temp));

  if (reverse == 0) {
    for (i = 0; i < bytes; i++) {
      //temp = src;
      dest[i] = temp[i];
    }
  } else {
    for (i = 0; i < bytes; i++) {
      //temp = src;
      dest[i] = temp[bytes - i -1];
    }
  }
}

void getbits( char dest[], int bytes, void *src, int start, int end) {

  //int bitsToCopy = start-end;
  unsigned char* temp = src;
  char tempDest[bytes*8+1];

  int startByte = bytes - start/8 -1;
  //printf("StartByte: %d\n", startByte);
  int endByte = bytes - end/8 -1;
  //printf("endByte: %d\n", endByte);

  int startBit = start%8;
  //printf("startBit: %d\n", startBit);
  int endBit = end%8;
  //printf("endbit: %d\n", endBit);

  int destCount = 0;
  //printf("dest[]: %s\n", dest);

  for (int k = startByte; k <= endByte; k++) {
    //printf("iteration: %d\n", f++);
    if (k == startByte && k != endByte) {
      for (int i = startBit; i >=0; i --) {
        if (1 & (temp[k] >> i)) {
          tempDest[destCount] = '1';
          //printf("%s\n", tempDest);
          destCount++;
        //  printf("%d\n", start - i);
        } else {
          tempDest[destCount] = '0';
          //printf("%s\n", tempDest);
          destCount++;
        }
      }
    } else if (k == endByte && k!= startByte) {
      for (int i = 7; i >endBit; i --) {
        if (1 & (temp[k] >> i)) {
          tempDest[destCount] = '1';
          //printf("%s\n", tempDest);
          destCount++;
        //  printf("%d\n", start - i);
        } else {
          tempDest[destCount] = '0';
          //printf("%s\n", tempDest);
          destCount++;
        }
      }
    } else if (k == endByte && k == startByte) {
      //printf("blah\n");
      for (int i = startBit; i >endBit; i --) {
        //printf("iterationsss: %d\n", f++);
        if (1 & (temp[k] >> i)) {
          tempDest[destCount] = '1';
          destCount++;
          //printf("%s\n", tempDest);
        //  printf("%d\n", start - i);
        } else {
          tempDest[destCount] = '0';
          //printf("%s\n", tempDest);
          destCount++;
        }
      }
    } else {
      for (int i = 7; i >=0; i --) {
        if (1 & (temp[k] >> i)) {
          tempDest[destCount] = '1';
          destCount++;
        //  printf("%d\n", start - i);
        } else {
          tempDest[destCount] = '0';
          destCount++;
        }
      }
    }

  }

  for (int i = 0; i < strlen(tempDest); i ++) {
    dest[i] = tempDest[i];
  }

  dest[destCount] = '\0';

}





long long bits2ll( char *bits) {
  long long temp = 0;
  int firstDigit = -1;
  int length = strlen(bits);

  for (int i = 0; i < length ; i++) {

    if (i > 0) {
      firstDigit = 1;
    }

    if (bits[i] == '1') {
      temp+=  (firstDigit *1LL<<(length -i -1));
      //printf("bit: %d\n",bits[length - i] - '0');
    }
  }
  printf( "%lld\n",temp);
  return temp;
}

unsigned long long bits2ull( char *bits) {
  unsigned long long temp = 0;
  //printf("%ld\n", strlen(bits));
  for (int i = 0; i < strlen(bits); i++) {
    temp<<=1LLU;
    temp += (bits[i] - '0');
  }
  //printf("%llu\n", temp );
  return(temp);
}

void spff( char *sign, char *exponent, char *significand, float *src) {

  unsigned char temp[32];

  getbits(temp[32], sizeof(float), src, 31, 0);





}

void dpff(char *sign, char *exponent, char *significand, double *src) {


}
