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

augmented_images, augmented_measurements = [], []
for image, measurment in zip(images, measurments):
    augmented_images.append(image)
    augmented_measurements.append(measurment)
    augmented_images.append(cv2.flip(image, 1))
    augmented_measurements.append(measurment*-1.0)

X_train = np.array(augmented_images)
y_train = np.array(augmented_measurements)

from keras.models import Sequential
from keras.layers import Flatten, Dense, Lambda
from keras.layers import Convolution2D, MaxPooling2D
from keras.layers import Dropout, Cropping2D


model = Sequential()
model.add(Lambda(lambda  x: x / 255.0 - 0.5, input_shape=(160,320,3)))
model.add(Cropping2D(cropping=((70,25),(0,0))))
model.add(Flatten())
model.add(Dense(1))
#nvida model
# model.add(Lambda(lambda x: (x / 255.0) - 0.5, input_shape=(160, 320, 3)))
# model.add(Cropping2D(cropping=((70,25), (0,0))))
# model.add(Convolution2D(24, 5, 5, subsample=(2, 2), activation='relu'))
# model.add(Convolution2D(36, 5, 5, subsample=(2, 2), activation='relu'))
# model.add(Convolution2D(48, 5, 5, subsample=(2, 2), activation='relu'))
# model.add(Convolution2D(64, 3, 3, activation='relu'))
# model.add(Convolution2D(64, 3, 3, activation='relu'))
# model.add(Dropout(0.25))
# model.add(Flatten())
# model.add(Dense(100, activation='relu'))
# model.add(Dropout(0.25))
# model.add(Dense(50, activation='relu'))
# model.add(Dropout(0.25))
# model.add(Dense(10, activation='relu'))
# model.add(Dropout(0.25))
# model.add(Dense(1, activation='tanh'))

model.compile(loss='mse', optimizer='adam')
model.fit(X_train, y_train, validation_split=0.2, shuffle=True, epochs=1)

model.save('model.h5')



