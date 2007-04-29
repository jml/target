
LIBS =

CDEBUG = -g
CFLAGS = $(CDEBUG) -I.
LDFLAGS = -g

OBJS = target.o

all: target

target: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f *.o target *.pyc

.PHONY: all target clean
