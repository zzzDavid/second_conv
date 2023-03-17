import numpy as np
# import checks as c
# import inputs as i
import py_inputs as i

# in_shape = (1, 16, 8, 8) # n, c, h, w
# weight_shape = (32, 16, 3, 3) # o, i, h, w
in_shape = (1, 2, 8, 8) # n, c, h, w
weight_shape = (4, 2, 3, 3) # o, i, h, w
# a_np = i.np_only0#c.np_conv_layer1.reshape(1,16,8,8)
# b_np = i.np_w2.reshape(32,16,3,3)
a_np = i.np_only1_2c#c.np_conv_layer1.reshape(1,16,8,8)
b_np = i.np_w2_2c

a_np = np.where(a_np > 0, 1, -1)
b_np = np.where(b_np > 0, 1, -1)
a_np = np.pad(a_np, ((0, 0), (0, 0), (1, 1), (1, 1)), 'constant')
n, c, h, w = in_shape
o, i, kh, kw = weight_shape
baseline_output = np.zeros((n, o, h, w))
for i in range(n):
        for j in range(o):
            for k in range(h):
                for l in range(w):
                    for m in range(c):
                        for p in range(kh):
                            for q in range(kw):
                                baseline_output[i][j][k][l] += a_np[i][m][k + p][l + q] * b_np[j][m][p][q]
out = baseline_output.flatten()
for i in range(4*8*8):
    print(int(out[i]),end=",")
