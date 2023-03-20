import numpy as np 


# input size: 1x16x8x8 (n, c_in, h, w)
# output size: 1x32x8x8 (n, c_out, h, w)
# kernel size: 32x16x3x3 (c_out, c_in, h, w)

# generate random binary input
input = np.random.randint(2, size=(1, 16, 8, 8)).astype(np.int32)

# generate random binary kernel
kernel = np.random.randint(2, size=(32, 16, 3, 3)).astype(np.int32)


# save input and kernel to file
# comma separated values, no new line
input = input.reshape(-1)
with open("input.txt", "w") as f:
    for index, i in enumerate(input):
        f.write(str(i))
        if i != len(input) - 1:
            f.write(",")

kernel = kernel.reshape(-1)
with open("kernel.txt", "w") as f:
    for index, i in enumerate(kernel):
        f.write(str(i))
        if i != len(kernel) - 1:
            f.write(",")