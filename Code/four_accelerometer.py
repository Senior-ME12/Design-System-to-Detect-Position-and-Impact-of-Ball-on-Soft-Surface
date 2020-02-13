import serial
#import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
#from datetime import datetime
#dt = datetime.now()
#dt.microsecond
import csv

ser = serial.Serial('COM12', 115200)

with open('middle.csv', 'w', newline ='') as f:
    writer = csv.writer(f)
    writer.writerow(['time','snsr_11','snsr_12','snsr_13','snsr_14',
                            'snsr_21','snsr_22','snsr_23','snsr_24',
                            'snsr_31','snsr_32','snsr_33','snsr_34',                           
                            'snsr_41','snsr_42','snsr_43','snsr_44','interupt'])
    
dummy = np.zeros((4,4))
fig, ax = plt.subplots()
line = ax.imshow(dummy, vmin=-50, vmax=50)

def init():
    line.set_array(np.zeros((4,4)))
    
    return line,

def animate(i):
    s = str(ser.readline(),'utf-8')
    st = s.rstrip().split(',')
    with open('middle.csv', 'a', newline ='') as f:
        writer = csv.writer(f)
        writer.writerow(st)
    lis = [float(x) for x in st[1:17]]
    a = np.array(lis).reshape(4,4)
    line.set_array(a)
    #line.text(0,-0.6,s)
    #line.set_title(s)
    return line,

ani = animation.FuncAnimation(
        fig, animate, init_func=init, interval=5, blit=True, save_count=10)

plt.show()
