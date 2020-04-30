CC = g++

CFLAGS = -Wall -std=c++17 -pthread -lwiringPi
AUFLAGS =
MAINFLAGS =


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MAINFLAGS += -lasound
	AUFLAGS += -D__LINUX_ALSA__
endif
ifeq ($(UNAME_S),Darwin)
	MAINFLAGS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
	AUFLAGS += -D__MACOSX_CORE__
endif


all: Looper

# Main

Looper : rtAudio_template.cpp looper.o RtAudio.o
	$(CC) -o $@ $(CFLAGS) $(AUFLAGS) $(MAINFLAGS) rtAudio_template.cpp looper.o RtAudio.o

RtAudio.o: RtAudio.cpp
	$(CC) -c -o $@ $(CFLAGS) $(AUFLAGS) RtAudio.cpp


clean:
	-rm -f *.o
	make
