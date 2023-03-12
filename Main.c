#include <stdio.h>

/* ビットマップを表示 */
void printBitmap(unsigned long bitmap) {
  int i, j;
  unsigned long b = 1;
  for (i = 7; i >= 0; i--) {
    for (j = 7; j >= 0; j--) {
      printf((bitmap & (b << (i * 8 + j))) > 0 ? "■" : "□");
    }
    printf("\n");
  }
}

/* 1バイトのビット列を逆転 */
unsigned long reverseByte(unsigned long byte) {
  byte = ((byte & 0x55) << 1) | ((byte & 0xAA) >> 1);
  byte = ((byte & 0x33) << 2) | ((byte & 0xCC) >> 2);
  byte = ((byte & 0x0F) << 4) | ((byte & 0xF0) >> 4);
  return byte;
}

/* 右上から左下の対角線を境界にビットマップを反転 */
unsigned long reverseSlant(unsigned long bitmap) {
  unsigned long result = 0;
  result |= (bitmap & 0x8000000000000000) >> 63;
  result |= (bitmap & 0x4080000000000000) >> 54;
  result |= (bitmap & 0x2040800000000000) >> 45;
  result |= (bitmap & 0x1020408000000000) >> 36;
  result |= (bitmap & 0x0810204080000000) >> 27;
  result |= (bitmap & 0x0408102040800000) >> 18;
  result |= (bitmap & 0x0204081020408000) >> 9;
  result |= (bitmap & 0x0102040810204080);
  result |= (bitmap & 0x0001020408102040) << 9;
  result |= (bitmap & 0x0000010204081020) << 18;
  result |= (bitmap & 0x0000000102040810) << 27;
  result |= (bitmap & 0x0000000001020408) << 36;
  result |= (bitmap & 0x0000000000010204) << 45;
  result |= (bitmap & 0x0000000000000102) << 54;
  result |= (bitmap & 0x0000000000000001) << 63;
  return result;
}

int main()
{
  unsigned long bitmap = 0b1111111111111111111000001111110011111100111000001110000011100000;
  printBitmap(bitmap);
  
  int i;
  unsigned long sideReversedBitmap = 0;
  for (i = 7; i >= 0; i--) {
    unsigned long byte = ((bitmap >> (8 * i)) & 0xFF);
    unsigned long rByte = reverseByte(byte);
    sideReversedBitmap |= (rByte << (8 * i));
  }
  printf("\n");
  printBitmap(sideReversedBitmap);
  
  unsigned long slantReversedBitmap = reverseSlant(sideReversedBitmap);
  printf("\n");
  printBitmap(slantReversedBitmap);
}
