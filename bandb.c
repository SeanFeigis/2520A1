//Author: Sean Feigis
//ID: 1096849
//All my function source code
#include <stdio.h>
#include <string.h>
#include "bandb.h"

void getbytes( unsigned char dest[], int bytes, void *src, int reverse) {
  int i;
  unsigned char* temp = src;


  if (reverse == 0) { //Does it in forward direction
    for (i = 0; i < bytes; i++) {
      dest[i] = temp[i]; //swaps the pointer value
    }
  } else { //reverse direction
    for (i = 0; i < bytes; i++) {
      dest[i] = temp[bytes - i -1]; //swaps the pointer value
    }
  }
}

void getbits( char dest[], int bytes, void *src, int start, int end) {

  //int bitsToCopy = start-end;
  unsigned char* temp = src; //casts src to a unsigned char
  char tempDest[bytes*8+1]; //creates a max value char array

  //does all the position calculations
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

  for (int k = endByte; k >= startByte; k--) { //cycles through how many bytes are encompassed
    //printf("iteration: %d\n", f++);
    if (k == startByte && k != endByte) { //the first byte to copy
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
    } else if (k == endByte && k!= startByte) { //the last byte to copy
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
    } else if (k == endByte && k == startByte) { //if its all in 1 byte
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
    } else { //inbetween bytes
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

  //Copies the temp char array into the dest
  for (int i = 0; i < strlen(tempDest); i ++) {
    dest[i] = tempDest[i];
  }
  //cuts off dest the appropriate amount
  dest[destCount] = '\0';

}





long long bits2ll( char *bits) {
  long long num = 0;
  int firstDigit = -1; //starts off the number as -1 for the 2s complement
  int length = strlen(bits);

  for (int i = 0; i < length ; i++) {

    if (i > 0) {
      firstDigit = 1; //first digit makes the first value add negative
    }

    if (bits[i] == '1') {
      num+=  (firstDigit *1LL<<(length -i -1)); //shifts the value to add from high to low
      //printf("bit: %d\n",bits[length - i] - '0');
    }
  }
  return num;
}

unsigned long long bits2ull( char *bits) {
  unsigned long long num = 0;
  //printf("%ld\n", strlen(bits));
  for (int i = 0; i < strlen(bits); i++) { //loops for size of char array
    num <<= 1LLU; //shifts everything to the left
    num += (bits[i] - '0'); //adds the integer equivalent value of the char in the array
  }
  //printf("%llu\n", temp );
  return(num);
}

void spff( char *sign, char *exponent, char *significand, float *src) {

  char num[32];
  getbits(num, sizeof(float), src, 31, -1); //copies the whole number in to a new char array

  //Disects the char array accordingly

  sign[0] = num[0];
  sign[1] = '\0';

  for (int i = 1; i < 9; i++) {
    exponent[i-1]= num[i];
  }
  exponent[8] = '\0';

  for (int i = 9; i < 32; i++) {
    significand[i - 9]= num[i];
  }
  significand[23] = '\0';

  //printf("%s\n", num);
}

void dpff(char *sign, char *exponent, char *significand, double *src) {

  char num[64];

  getbits(num, sizeof(double), src, 63, -1); //copies the whole number in to a new char array

  //Disects the char array accordingly

  sign[0] = num[0];
  sign[1] = '\0';

  for (int i = 1; i < 12; i++) {
    exponent[i-1]= num[i];
  }
  exponent[11] = '\0';

  for (int i = 12; i < 64; i++) {
    significand[i - 12]= num[i];
  }
  significand[52] = '\0';

}
