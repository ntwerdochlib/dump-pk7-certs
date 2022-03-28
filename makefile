CFLAGS = -I/home/nik/source/3rdparty/openssl-1.0.1k/linux64/include 
#LFLAGS = -m elf_x86_64 -L/home/nik/source/3rdparty/openssl-1.0.1k64/linux/lib -lcrypto
#LFLAGS = -m elf_x86_64 -L/home/nik/source/3rdparty/openssl-1.0.1k/linux64/lib
#LFLAGS = -m elf_x86_64 -ldl
LFLAGS = -m64 -ldl

#gcc -o pk7dump main.c -lcrypto -I-L../3rdparty/openssl-1.0.1k/linux/lib

SRCS = main.c
OBJS = $(SRCS:.c=.o)

.c.o:
	gcc -c $(CFLAGS) $<

pk7-dump: $(OBJS)
	gcc -o $@ $(LFLAGS) $(OBJS) -lcrypto
