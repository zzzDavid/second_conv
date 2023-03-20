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

output = np.zeros((n, o, h, w)) 
# padding
input = np.pad(input, ((0, 0), (0, 0), (1, 1), (1, 1)), 'constant', constant_values=(0, 0))

first = 0
for cc in range(c):
    for hh in range(3):
        for ww in range(3):
            inp = input[0, cc, hh, ww]
            ker = kernel[0, cc, hh, ww]
            print(f"input[0][{cc}][{hh}][{ww}] = {inp}, kernel[0][{cc}][{hh}][{ww}] = {ker}")
            inp = 1 if inp == 1 else -1
            ker = 1 if ker == 1 else -1
            first += inp * ker
print(f"first = {first}")

# convolution
for nn in range(n):
    for oo in range(o):
        for hh in range(h):
            for ww in range(w):
                for cc in range(c):
                    for kkh in range(kh):
                        for kkw in range(kw):
                            inp = input[nn, cc, hh + kkh, ww + kkw]
                            ker = kernel[oo, cc, kkh, kkw]
                            inp = 1 if inp == 1 else -1
                            ker = 1 if ker == 1 else -1
                            output[nn, oo, hh, ww] += inp * ker

# save output to file
output = output.reshape(-1)
with open("output.txt", "w") as f:
    for index, i in enumerate(output):
        f.write(str(int(i)))
        if i != len(output) - 1:
            f.write("\n")