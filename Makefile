BINARIES= NaiveBayes
all: ${BINARIES}

NaiveBayes: 
	g++ CS165Amp2.cpp -o gobang
clean:
	/bin/rm -f ${BINARIES} *.o
