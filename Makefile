# Имя компилятора
CC=g++

# Стандарт
STD=c++11

.PHONY: all

all: exec clear

exec: influxdb.o FLinfluxDB.o MosqMQTTWrapper.o main.o 
	$(CC) -I"/usr/local/include" -L"/usr/local/lib" influxdb.o FLinfluxDB.o MosqMQTTWrapper.o main.o -o exec -lmosquitto -lmosquittopp 
influxdb.o:
	$(CC) -std=$(STD) -c influxdb.hpp -o influxdb.o
main.o:
	$(CC) -std=$(STD) -c main.cpp -o main.o
FLinfluxDB.o: FLinfluxDB.hpp
	$(CC) -std=$(STD) -c FLinfluxDB.cpp -o FLinfluxDB.o 
MosqMQTTWrapper.o: MosqMQTTWrapper.hpp
	$(CC) -std=$(STD) -c MosqMQTTWrapper.cpp -o MosqMQTTWrapper.o
clear:
	rm -rf *.o
