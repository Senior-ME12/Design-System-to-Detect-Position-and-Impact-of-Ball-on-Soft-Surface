import serial
#import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
#from datetime import datetime
#dt = datetime.now()
#dt.microsecond
import csv

ser = serial.Serial('COM13', 115200)

with open('mycvs.csv', 'w', newline ='') as f:
    writer = csv.writer(f)
    writer.writerow(['day','time','snsr_11','snsr_12','snsr_21','snsr_22'])
    
dummy = np.zeros((2,2))
fig, ax = plt.subplots()
line = ax.imshow(dummy, vmin=-50, vmax=50)

def init():
    line.set_array(np.zeros((2,2)))
    
    return line,

def animate(i):
    s = str(ser.readline(),'utf-8')
    st = s.rstrip().split(',')
    with open('mycvs.csv', 'a', newline ='') as f:
        writer = csv.writer(f)
        writer.writerow(st)
    lis = [float(x) for x in st[2:]]
    a = np.array(lis).reshape(2,2)
    line.set_array(a)
    #line.text(0,-0.6,s)
    #line.set_title(s)
    return line,

ani = animation.FuncAnimation(
    fig, animate, init_func=init, interval=5, blit=True, save_count=10)

plt.show()
