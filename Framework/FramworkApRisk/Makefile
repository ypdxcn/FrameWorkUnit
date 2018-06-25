#Makefile for 
# AIX version

.SUFFIXES:
.SUFFIXES: .cpp .obj .o

CPP = g++

KERNEL_INC = -I../Utility -I../NetMgr -I../CommFramwork -I../FramworkAp -I ../FramworkNm

CPPFLAGS =  -g -Wall  -O2 
CPPDEFS = -DLINUX -DUNIX -DNDEBUG -D_THREAD_SAFE -D_MT -DSA_USE_PTHREAD -D_AIX32_THREADS 

.cpp.o:
	$(CPP) $(CPPFLAGS) -c  $(CPPDEFS) $(KERNEL_INC) $< -o $@

OBJL = SmsPacket.o ProcessInterfaceA1C.o ProcessInterfaceA2C.o ProcessInterfaceF1S.o ProcessInterfaceF2S.o ProcessInterfaceSmscService.o

ALL:  libframworkaprisk.a  clean

libframworkaprisk.a: $(OBJL)
	ar rv $@ $(OBJL)
	mv $@ $(HOME)/lib
clean:
	rm -f *.o

