# * --------------------------------------------------------------------------------
# * "THE BEER-WARE LICENSE" (Revision 42):
# * <julien.deantoni@univ-cotedazur.fr> wrote this file.
# * As long as you retain this notice you can do whatever you want with this stuff.
# * If we meet some day, and you think this stuff is worth it,
# * you can buy me a beer in return.  Julien Deantoni
# * --------------------------------------------------------------------------------
# */

#!/usr/bin/python3
from tkinter import LEFT,RIGHT,INSERT,BOTH,Y,X,BOTTOM
from tkinter import Tk
from tkinter import Label
from tkinter import Entry
from tkinter import Button
from tkinter import scrolledtext
from datetime import datetime
from tkinter import Frame
from tkinter import Checkbutton
from tkinter import IntVar

from serial import *



#CONFIG !
PORT="/dev/ttyACM0"
BAUD=9600

window = Tk()
window.title("Polytech Simple Serial Monitor/Injector")
window.geometry('550x600')
window.configure(background='#49A')
def exit(Event=None):
    window.destroy()
window.bind("<Escape>", exit)

sendingFrame = Frame(window, background='#49A')
sendingFrame.pack(fill=X, expand='yes')

lbl = Label(sendingFrame, text="Input:", fg="white", background='#49A')
lbl.pack(side=LEFT)

inputEntry = Entry(sendingFrame, background='white')
inputEntry.pack(side=LEFT, fill=X, expand=1,padx=20, pady=20)

asInt = IntVar();
checkbox = Checkbutton(sendingFrame, text="as Number", variable=asInt)
checkbox.pack(side=LEFT, fill=X, padx=20, pady=20)

btn = Button(sendingFrame, text="  Send  ")
btn.pack(side=LEFT)

outputFrame = Frame(window, background='#49A')
outputFrame.pack(fill=BOTH, expand=1)

output = scrolledtext.ScrolledText(outputFrame, background='white')
output.pack(fill=BOTH,expand=1)


def sendClicked(event=None):
    # current date and time
    now = datetime.now()
    temp = "   -->   "+str(now)+": "+inputEntry.get()+"\n"
    if(asInt.get() == 0):
        serialPort.write((inputEntry.get()).encode('ascii'))
    else:
        serialPort.write(int(inputEntry.get()).to_bytes(1, 'little'));#int(inputEntry.get()))
    output.insert(INSERT,temp)

btn.config(command=sendClicked)
inputEntry.bind('<Return>', sendClicked)
serialPort = Serial(port=PORT, baudrate=BAUD, timeout=1, writeTimeout=1)

def readSerial():
    if serialPort.isOpen():
            receivedData = serialPort.readline().decode()
            if (len(receivedData) > 0):
                now = datetime.now()
                temp = "<--      "+str(now)+": "+str(receivedData)
                output.insert(INSERT,temp)
    output.after(500, readSerial)


readSerial()
window.mainloop()
