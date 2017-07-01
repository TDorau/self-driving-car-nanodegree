import csv
import os
import cv2
import numpy as np

# preprocessing as seen in the forum, image dimsensions 64x64 + normalization
def prep_image(image):
    image = image[55:135, :, :]
    image = cv2.resize(image, (64, 64))
    image = image.astype(np.float32)
    image = image / 255.0 - 0.5
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    return image

lines = []
with open(os.path.join("Udata", "driving_log.csv")) as csvfile:
    reader = csv.reader(csvfile)
    for line in reader:
        lines.append(line)

images = []
measurements = []
for line in lines:
    source_path = line[0]
    filename = source_path.split('/')[-1]
    current_path = os.path.join("Udata", "IMG", filename)
    image = cv2.imread(current_path)
    image = prep_image(image)
    images.append(image)
    measurement = float(line[3])
    measurements.append(measurement)

augmented_images, augmented_measurements = [], []
for image, measurement in zip(images, measurements):
    augmented_images.append(image)
    augmented_measurements.append(measurement)
    augmented_images.append(cv2.flip(image, 1))
    augmented_measurements.append(measurement * -1.0)

X_train = np.array(augmented_images)
y_train = np.array(augmented_measurements)

from keras.models import Sequential
from keras.layers import Flatten, Dense, Lambda
from keras.layers import Convolution2D, MaxPooling2D, ELU
from keras.layers import Dropout, Cropping2D

# model.add(Lambda(lambda  x: x / 255.0 - 0.5, input_shape=(160,320,3)))
# model.add(Lambda(resize_function, input_shape=(160,320,3)))
# model.add(Cropping2D(cropping=((70,25),(0,0))))
# model.add(Cropping2D(cropping=((70, 25), (1, 1)), input_shape=(160, 320, 3)))
model = Sequential()
# model.add(Convolution2D(24,5,5,subsample=(2,2),input_shape=(64, 64, 3), activation='relu'))
model.add(Convolution2D(1,1,1, border_mode = 'same',init ='glorot_uniform',input_shape=(64, 64, 3)))
model.add(Convolution2D(24,5,5,subsample=(2,2), activation='relu'))
model.add(Convolution2D(24,5,5,subsample=(2,2), activation='relu'))
model.add(Convolution2D(36,5,5,subsample=(2,2), activation='relu'))
model.add(Convolution2D(48,5,5,subsample=(2,2), activation='relu'))
# model.add(Dropout(0.2
# model.add(Convolution2D(64,3,3,activation='relu'))
# model.add(Convolution2D(64,3,3,activation='relu'))
model.add(Flatten())
model.add(Dense(100, activation='relu'))
# model.add(Dropout(0.25))
model.add(Dense(50, activation='relu'))
# model.add(Dropout(0.25))
model.add(Dense(10, activation='relu'))
# model.add(Dropout(0.25))
model.add(Dense(1))

model.compile(loss='mse', optimizer='adam')
# model.fit(X_train, y_train, validation_split=0.2, shuffle=True, epochs=1)
model.fit(X_train, y_train, validation_split=0.2, shuffle=True, nb_epoch=3)

model.save('model.h5')
