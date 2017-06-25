import csv
import os
import cv2
import numpy as np


lines = []
with open(os.path.join("Simulationdata", "driving_log.csv")) as csvfile:
#with open(os.path.join("data", "driving_log.csv")) as csvfile:
    reader = csv.reader(csvfile)
    for line in reader:
        lines.append(line)

images = []
measurments = []
for line in lines:
    source_path = line[0]
    filename = source_path.split('\\')[-1]
    current_path = os.path.join("Simulationdata", "IMG", filename)
    image = cv2.imread(current_path)
    images.append(image)
    measurment = float(line[3])
    measurments.append(measurment)

X_train = np.array(images)
y_train = np.array(measurments)

from keras.models import Sequential
from keras.layers import Flatten, Dense, Lambda
from keras.layers import Convolution2D

model = Sequential()
model.add(Lambda(lambda x: (x / 255) - 0.5, input_shape=(160,320,3)))
model.add(Flatten())
model.add(Dense(1))

model.compile(loss='mse', optimizer='adam')
model.fit(X_train, y_train, validation_split=0.2, shuffle=True, epochs=1)

model.save('model.h5')



