import numpy as np

in_shape = (1, 16, 8, 8) # n, c, h, w
weight_shape = (32, 16, 3, 3) # o, c, h, w

n, c, h, w = in_shape
o, c, kh, kw = weight_shape

# read in input and kernel
input_file = "../input.txt"
kernel_file = "../kernel.txt"


with open(input_file, "r") as f:
    input = f.read().split(",")
    # remove empty string
    input = list(filter(None, input))
    input = np.array(input).astype(np.int32)
    input = input.reshape(n, c, h, w)

with open(kernel_file, "r") as f:
    kernel = f.read().split(",")
    # remove empty string
    kernel = list(filter(None, kernel))
    kernel = np.array(kernel).astype(np.int32)
    kernel = kernel.reshape(o, c, kh, kw)

# 0 in input and kernel means -1
input[input == 0] = -1
kernel[kernel == 0] = -1

output = np.zeros((n, o, h, w)) 
# padding
input = np.pad(input, ((0, 0), (0, 0), (1, 1), (1, 1)), 'constant', constant_values=(-1, -1))
# convolution
for i in range(n):
    for j in range(o):
        for k in range(h):
            for l in range(w):
                for m in range(c):
                    for p in range(kh):
                        for q in range(kw):
                            output[i][j][k][l] += input[i][m][k + p][l + q] * kernel[j][m][p][q]

# save output to file
output = output.reshape(-1)
with open("output.txt", "w") as f:
    for index, i in enumerate(output):
        f.write(str(int(i)))
        if i != len(output) - 1:
            f.write("\n")