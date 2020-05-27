import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext
from tkinter import Menu

import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import serial #pyserial
import time

import heartpy as hp
import csv

win = tk.Tk()
win.title("Python GUI")

# #-------------
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
#-----------------
msg2 = '0001'
count = 0
flg = False
flg2 = False
msg = '0001'
ser = serial.Serial()
#--------------
MAX_ECG = 3920
BPM = 0.0
Pulse_1 = False
PulseTime_1 = 0
PulseTime_2 = 0
#------------------

tabControl = ttk.Notebook(win)

tab1 = ttk.Frame(tabControl)
tabControl.add(tab1, text='Input')

tabControl.pack(expand=1, fill="both")
#----------------------------------
monty = ttk.LabelFrame(tab1, text='')
monty.grid(column=0, row=0)
#-------------------------------------

def clickMe():
    ser.baudrate = name.get()
    ser.port = "COM"+ (number.get())
    print ("COM"+ (number.get()))
    ser.open()
    if ser.is_open:
        action.configure(text='Valid')
        global flg 
        flg = True

ttk.Label(monty, text="Enter Baud Rate (9600 Recommended):").grid(column =0,row=0, sticky='W')

name = tk.StringVar()
nameEntered = ttk.Entry(monty, width=12, textvariable=name)
nameEntered.grid(column=0, row=1, sticky='W')

ttk.Label(monty, text="Choose a port number:").grid(column=1, row=0, sticky='W', padx=20)

number = tk.StringVar()
numberChosen = ttk.Combobox(monty, width=12, textvariable=number, state="readonly")
numberChosen['values'] = (3,4,5)
numberChosen.grid(column=1, row=1)

action = ttk.Button(monty, text="Check Connection", command=clickMe)
action.grid(column=2, row=1)

#---------------
def limitSizeRate(*args):
   
    if int(rateValue.get()) <= 0:
        rateValue.set('1')
        ttk.Label(monty, text="Minimum Rate: 1 - (150 recommended)").grid(column =0,row=2, sticky='W')
    elif int(rateValue.get()) > 1501: 
        rateValue.set(1500)
        ttk.Label(monty, text="Maximum Rate: 1500 - (150 recommended)").grid(column =0,row=2, sticky='W')


ttk.Label(monty, text="Enter Sample Rate (150 Recommended):").grid(column =0,row=2, sticky='W')

rateValue = tk.StringVar()
rateValue.trace('w', limitSizeRate)
rateValue.set('1')

rateEntered = ttk.Entry(monty, width=12, textvariable=rateValue)
rateEntered.grid(column=0, row=3, sticky = tk.W)

#--------------------------

def close_event():
    global flg
    flg = False
    global count
    global msg2
    ser.close()
    count = 0
    action.configure(text='Check Connection')
    timer.stop()

timer = fig.canvas.new_timer(interval = int(msg2)*65*1000) 
timer.add_callback(close_event)



def clickMe2():
    xs = []
    ys = []
    global msg2
    global flg
    if int(rateValue.get()) < 10:
        msg2 = '000'+str(rateValue.get())
    elif int(rateValue.get()) < 100:
        msg2 = '00'+str(rateValue.get())
    elif int(rateValue.get()) < 1000:
        msg2 = '0'+str(rateValue.get()) 
    elif int(rateValue.get()) > 1000 and int(rateValue.get()) < 1501:
        msg2 = str(rateValue.get()) 
    elif int(rateValue.get()) > 1501: 
        msg2 = '1500'

    msg ='ss' + msg2 + 'ss'
    msg = msg.encode('utf-8')

    if flg == True:
        ser.write(msg)

        def animate(i, xs, ys):
            global count
            global MAX_ECG
            global Pulse_1
            global PulseTime_1
            global PulseTime_2
            # Read ADC Data
            if count < int(msg2)*60 and flg == True:
                msgg = ser.read(4)
                count = count + 1
                msg3 = msgg.decode("utf-8")
                if msg3[0] == '0':
                        msg3 = '0'
                msg4 = int(msg3)


                if msg4 > MAX_ECG:
                        if Pulse_1 == False:
                                PulseTime_1 = dt.datetime.now()
                                Pulse_1 = True
                        else:
                                PulseTime_2 = dt.datetime.now()
                                PulseInterval = PulseTime_2 - Pulse_1
                                BPM = (1.0/PulseInterval.total_seconds()) * 60.0 
                                ttk.Label(monty, text="BPM is: " + str(BPM)).grid(column =1,row=3, sticky='W')
                                Pulse_1 = False
               

                # Add x and y to lists
                xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
                ys.append(msg4)

                # Limit x and y lists to 200 items
                xs = xs[-200:]
                ys = ys[-200:]

                # Draw x and y lists
                ax.clear()
                ax.plot(xs, ys)

                # Format plot
                plt.xticks(rotation=45, ha='right')
                plt.subplots_adjust(bottom=0.30)
                plt.title('ECG Signals Over Time')
                plt.ylabel('ECG Signals')
        timer.start()

        ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000.0/int(msg2))
        plt.show()
        
    
action2 = ttk.Button(monty, text="Start Sampling", command=clickMe2)
action2.grid(column=2, row=3)



nameEntered.focus()
win.mainloop()
