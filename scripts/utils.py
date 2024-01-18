import numpy as np


class ScrollingBuffer(object):
    def __init__(self, max_size=1000):
        self.max_size = max_size
        self.offset = 0
        self.data = np.zeros(shape=(2, self.max_size))
        print(f"test: {self.data[1, self.max_size-1]}")

    def add_point(self, x: float, y: float):
        if self.data.shape[1] < self.max_size:
            self.data = np.append(self.data, [x, y])
        else:
            self.data[:, self.offset] = np.array([x, y])
            self.offset = (self.offset + 1) % self.max_size

    def erase(self):
        if self.data.shape[1] > 0:
            self.data = np.zeros(2, self.max_size)
            self.offset = 0
