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
    print('tooozzzzzz')
    global flg
    flg = False
    global count
    ser.close()
    count = 0
    timer.stop()

timer = fig.canvas.new_timer(interval = int(msg2)*12*1000) #creating a timer object and setting an interval of 3000 milliseconds
timer.add_callback(close_event)



def clickMe2():

    print('clickme')
    # ax = fi
    # g.add_subplot(1, 1, 1)
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
    # Read temperature (Celsius) from TMP102
            if count < int(msg2)*10:
                msgg = ser.read(4)
                count = count + 1
                print(count)
                msg3 = msgg.decode("utf-8")
                if msg3[0] == '0':
                        msg3 = '0'
                msg4 = int(msg3)

                # Add x and y to lists
                xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
                ys.append(msg4)

                # Limit x and y lists to 20 items
                xs = xs[-20:]
                ys = ys[-20:]

                # Draw x and y lists
                ax.clear()
                ax.plot(xs, ys)

                # Format plot
                plt.xticks(rotation=45, ha='right')
                plt.subplots_adjust(bottom=0.30)
                plt.title('TMP102 Temperature over Time')
                plt.ylabel('Temperature (deg C)')
                
        print(msg)
        print(count)
        timer.start()

        ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000.0/int(msg2))
        plt.show()
        
       
    
action2 = ttk.Button(monty, text="Start Sampling", command=clickMe2)
action2.grid(column=2, row=3)



nameEntered.focus()
win.mainloop()
