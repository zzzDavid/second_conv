#ifndef HLS
#define HLS

const bool w_conv2[32*16*3*3] = {
    #include"../kernel.txt"
}; //binary weight

const bool input[1*16*8*8] = {
    #include"../input.txt"
}; //binary input

void top(
  bool v0[1][16][8][8],
  bool v1[32][16][3][3],
  int32_t v2[1][32][8][8]
);
#endif