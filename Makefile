# vim: set ts=4 sw=4 nowrap:
# If you don't use CC
CC			= gcc
PREFIX		= /usr

# Setup our variables
EASEVER		= "0.0.4"
MAN_PATH	= ${PREFIX}/share/man/man3
LIBPATH		= ${PREFIX}/lib
BINPATH		= ${PREFIX}/bin
LIBFLAGS	= -shared -W1,-soname
BINFLAGS	= -Wall -g -c
CFLAGS		+= -I${PREFIX}/include -Wall -fpic -g -c -o
LDFLAGS		+= -L${LIBPATH}
SRCS		= libease.c
OBJS		= ${SRCS:.c=.o}

all: libease.so.${EASEVER}

# Build the libease library
libease.so.${EASEVER}: $(OBJS)
	@echo Building ease library
	@${CC} ${LIBFLAGS},${@:.${EASEVER}=.0} -o $@ ${OBJS} -lc
	@echo Done, Please type \'make install\' to install.

# Build our .o file from our .c file using flags
libease.o:
	@install ease.h ${PREFIX}/include/
	@${CC} ${CFLAGS} ${OBJS} ${SRCS}

# Install libease into the system
install:
	@echo 'Copying libease.so.${EASEVER} -> ${LIBPATH}'
	# Copy our library to the correct path
	@install libease.so.${EASEVER} ${LIBPATH}
	# Run ldconfig to install shared library
	@ldconfig
	@echo 'Linking ${LIBPATH}/libease.so.${EASEVER} -> ${LIBPATH}/libease.so'
	# Link our access file in
	@ln -s ${LIBPATH}/libease.so.${EASEVER} ${LIBPATH}/libease.so
	@echo 'Copying ease.h -> ${PREFIX}/include/'
	# Install the header file
	@install ease.h ${PREFIX}/include/
	@echo 'Installing libease.3 -> ${MAN_PATH}/libease.3'
	@install libease.3 $(MAN_PATH)
	# Rerun ldconfig (bug fix #122)
	@ldconfig
	@echo Done, Please type \'make test\' to ensure that the
	@echo library was installed properly.

# Uninstall libease from the system
uninstall:
	# Remove all our library files and the header files
	@rm -f ${LIBPATH}/libease*
	@rm -f ${PREFIX}/include/ease.h
	# Clean up our symbols
	@ldconfig

# Clean up the build invironment
clean:
	@echo Removing all object files
	# Remove any files from our last build
	@rm -f ${OBJS} libease.so.${EASEVER} ease ease.o
	@echo Done

# Run a test to check libease built correctly
test:
	# Create our test .o file
	@echo Compiling test executable
	@${CC} ${BINFLAGS} ease.c -o ease.o

	# Link in our library
	@${CC} -g -o ease ease.o -I/usr/include -L${LIBPATH} -lease

	# Execute our tests
	@echo Running our test
	@./ease none in out io oi bi bo ki ko kb
	@echo Done
	@echo If you would like to execute the test manually,
	@echo please run ./ease from within this directory.
