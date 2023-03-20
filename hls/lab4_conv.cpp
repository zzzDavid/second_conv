//==========================================================================
// layer.cpp
//==========================================================================
// @brief: this file contains all layers
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <math.h>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include "lab4_conv.h"
#include <cmath>
#include <iostream>

using namespace std;
int main(){
  bit mem_conv2[MAX_FMAP];
  // clear mem_conv2
  for (int i = 0; i< MAX_FMAP; i++){
    mem_conv2[i] = 0;
  }
  int mem_conv3[MAX_FMAP];
  ofstream myfile;
  pad(input, mem_conv2, 16, I_WIDTH2);
  conv2(mem_conv2, mem_conv3, 16, 32, I_WIDTH2+PADDING);
  myfile.open ("output.txt", std::ios::app);
  for (int j = 0; j< 32*8*8; j++){
    myfile << mem_conv3[j]<<"\n";
  }
  myfile.close();
}
// helper function to neglect padding pixels
inline bool if_mac(int x, int y, int I)
{
        if (x < PADDING / 2 || x >= (I - PADDING / 2) || y < PADDING / 2 || y >= (I - PADDING / 2))
                return false;
        return true;
}

//----------------------------------------------------------
// Padding
//----------------------------------------------------------
// @param[in] : input - input fmaps
//              M - number of input fmaps
//              I - width of input fmaps
// @param[out] : output - output fmaps

void pad(const bit input[MAX_FMAP], bit output[MAX_FMAP], int M, int I) {
  int ifmap_size = I * I;
  int ofmap_size = (I+PADDING) * (I+PADDING);

  for (int i = 0; i < MAX_FMAP; i++) output[i] = 0;

  for (int m = 0; m < M; m++) {
    for (int x = 0; x < I; x++) {
      for (int y = 0; y < I; y++) {
        int i_index = x + y*I + m*ifmap_size;
        int o_index = (x + PADDING/2) + (y + PADDING/2)*(I + PADDING) + m*ofmap_size;
        output[o_index] = input[i_index];
      }
    }
  }
}

//----------------------------------------------------------
// Perform Convolution Layer
//----------------------------------------------------------
// @param[in] : input - input fmaps
//              threshold - threshold for batchnorm operation
//              M - number of input fmaps
//              N - number of output fmaps
//              I - width of input fmaps
//              L - id for conv layers: 0 means conv1, 1 means conv2
// @param[out] : output - output fmaps

//----------------------------------------------------------
// Perform Convolution Layer
//----------------------------------------------------------
// @param[in] : input - input fmaps
//              threshold - threshold for batchnorm operation
//              M - number of input fmaps
//              N - number of output fmaps
//              I - width of input fmaps
// @param[out] : output - output fmaps

void conv2(bit input[MAX_FMAP], int output[MAX_FMAP], int M, int N, int I)
{
  int O = I - F + 1;
  int ifmap_size = I * I;
  int ofmap_size = O * O;
  
  // MAC and batchnorm
  LOOP_N: for (int n = 0; n < N; n++){
    LOOP_X: for (int x = 0; x < O; x++){
      LOOP_Y: for (int y = 0; y < O; y++){
        int sum = 0;
        int o_index = x + y * O + n * ofmap_size;
        LOOP_M: for (int m = 0; m < M; m++){
          int one_out = 0;
          int mac_num = 0;
          LOOP_C: for (int c = 0; c < F; c++){
            LOOP_R: for (int r = 0; r < F; r++){
              if (if_mac(x + c, y + r, I)) { //neglect padding pixels in mac
                int i_index = x + c + (y + r) * I + m * ifmap_size;
                int w_index = c + r * F + (n + m * N) * FILTER_SIZE;
                one_out += input[i_index] == w_conv2[w_index];
                mac_num++;
              }
            }
          }
          sum += (one_out << 1) - mac_num;
        }
        output[o_index] = sum; 
      }
    }
  }
}