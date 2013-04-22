import serial
import time
import threading

delay = 0.25

s = serial.Serial('/dev/ttyU0', 9600)
time.sleep(2);

def on():
	s.write('on;')

def off():
	s.write('off;')

def neutral():
	s.write('lr:90;ll:90;ur:90;ul:90;')
	time.sleep(delay);

def forward(steps):
	for step in range(steps):
		if step % 2 == 0:
			## right
			s.write('lr:100;ll:130;')
			time.sleep(delay/3)
			s.write('ur:60;ul:60;')
			time.sleep(delay)
			s.write('lr:90;ll:90;')
			time.sleep(delay/3)

		if step % 2 != 0:
			## left
			s.write('lr:50;ll:80;')
			time.sleep(delay/3)
			s.write('ur:120;ul:120;')
			time.sleep(delay)
			s.write('lr:90;ll:90;')
			time.sleep(delay/3)

if __name__ == '__main__':
	on()
	neutral()

	forward(10)

	neutral()
	off()

