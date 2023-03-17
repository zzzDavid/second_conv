//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <math.h>
#include <stdint.h>
#include "hls_second_conv.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(){
    int32_t v2[1][32][8][8];
    top(only_1,w_conv2,v2);
    ofstream myfile;
    myfile.open ("compare_second_conv.py", std::ios::app);
    myfile << "import numpy as np \n";
    myfile << "hls_cpp_only1= np.array([";
    for (int i=0; i<32;i++){
        for(int j=0; j<8; j++){
            for(int m=0;m<8;m++){
                myfile << v2[0][i][j][m]<<",";
      }
    }
  }
}
void top(
  bool v0[1][16][8][8],
  bool v1[32][16][3][3],
  int32_t v2[1][32][8][8]
) {     // L28
  bool conv2_pad[1][16][10][10];        // L480
  l_cc: for (int cc = 0; cc < 16; cc++) {       // L480
    l_hh: for (int hh = 0; hh < 10; hh++) {     // L480
      l_ww: for (int ww = 0; ww < 10; ww++) {   // L480
        ap_int<33> v7 = ww;     // L480
        ap_int<33> v8 = 1;      // L480
        bool v9 = v7 >= v8;     // L480
        bool v10 = 1 & v9;      // L30
        ap_int<33> v11 = 9;     // L480
        bool v12 = v7 < v11;    // L480
        bool v13 = v10 & v12;   // L30
        ap_int<33> v14 = hh;    // L480
        bool v15 = v14 >= v8;   // L480
        bool v16 = v13 & v15;   // L30
        bool v17 = v14 < v11;   // L480
        bool v18 = v16 & v17;   // L30
        bool v19 = v0[0][cc][(hh - 1)][(ww - 1)];       // L13
        bool v20 = 0;   // L480
        bool v21 = v18 ? (bool)v19 : (bool)v20; // L135
        conv2_pad[0][cc][hh][ww] = v21; // L480
      }
    }
  }
  l_ff: for (int ff = 0; ff < 32; ff++) {       // L480
    l_yy: for (int yy = 0; yy < 8; yy++) {      // L480
      l_xx: for (int xx = 0; xx < 8; xx++) {    // L480
        int32_t conv2_sum;      // L264
        conv2_sum = 0;  // L480
        l_rc: for (int rc = 0; rc < 16; rc++) { // L264
          l_ry: for (int ry = 0; ry < 3; ry++) {        // L264
            l_rx: for (int rx = 0; rx < 3; rx++) {      // L264
              if (1) {  // L480
                int64_t v29 = xx;       // L480
                int64_t v30 = 1;        // L480
                int64_t v31 = v29 * v30;        // L480
                int64_t v32 = rx;       // L480
                int64_t v33 = v32 * v30;        // L85
                ap_int<65> v34 = v31;   // L480
                ap_int<65> v35 = v33;   // L480
                ap_int<65> v36 = v34 + v35;     // L480
                ap_int<65> v37 = 1;     // L480
                bool v38 = v36 >= v37;  // L480
                bool v39 = 1 & v38;     // L30
                ap_int<65> v40 = 9;     // L480
                bool v41 = v36 < v40;   // L480
                bool v42 = v39 & v41;   // L30
                int64_t v43 = yy;       // L480
                int64_t v44 = v43 * v30;        // L480
                int64_t v45 = ry;       // L480
                int64_t v46 = v45 * v30;        // L85
                ap_int<65> v47 = v44;   // L480
                ap_int<65> v48 = v46;   // L480
                ap_int<65> v49 = v47 + v48;     // L480
                bool v50 = v49 >= v37;  // L480
                bool v51 = v42 & v50;   // L30
                bool v52 = v49 < v40;   // L480
                bool v53 = v51 & v52;   // L30
                bool v54 = conv2_pad[0][rc][(yy + ry)][(xx + rx)];      // L480
                ap_int<33> v55 = 1;     // L480
                ap_int<33> v56 = v54;   // L480
                ap_int<33> v57 = v55 - v56;     // L480
                bool v58 = v1[ff][rc][ry][rx];  // L14
                ap_int<33> v59 = v58;   // L480
                ap_int<33> v60 = v57 ^ v59;     // L480
                ap_int<33> v61 = v60 << v55;    // L480
                bool v62 = v55 >= 33;   // L480
                ap_int<33> v63 = v62 ? (ap_int<33>)0 : (ap_int<33>)v61; // L480
                ap_int<34> v64 = v63;   // L480
                ap_int<34> v65 = 1;     // L480
                ap_int<34> v66 = v64 - v65;     // L480
                int32_t v67 = v66;      // L480
                int32_t v68 = v53 ? (int32_t)v67 : (int32_t)0;  // L135
                int32_t v69 = conv2_sum;        // L264
                ap_int<33> v70 = v68;   // L480
                ap_int<33> v71 = v69;   // L480
                ap_int<33> v72 = v70 + v71;     // L135
                int32_t v73 = v72;      // L480
                conv2_sum = v73;        // L480
              }
            }
          }
        }
        int32_t v74 = conv2_sum;        // L264
        v2[0][ff][yy][xx] = v74;        // L480
      }
    }
  }
}