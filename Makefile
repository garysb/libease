# vim: set ts=4 sw=4 nowrap:
# If you don't use CC
CC			= gcc
PREFIX		= /usr
# Setup our variables
MAN_PATH	= ${PREFIX}/man/man1
LIBPATH		= ${PREFIX}/lib
BINPATH		= ${PREFIX}/bin
LIBFLAGS	= -shared -W1,-soname
BINFLAGS	= -Wall -g -c
CFLAGS		+= -I${PREFIX}/include -Wall -fpic -g -c -o
LDFLAGS		+= -L${LIBPATH}
SRCS		= libease.c
OBJS		= ${SRCS:.c=.o}

all: libease.so.0.0.1

libease.so.0.0.1: $(OBJS)
	@echo Building ease library
	@${CC} ${LIBFLAGS},${@:.0.0.1=.0} -o $@ ${OBJS} -lc		# Create our library
	@echo Done, Please type \'make install\' to install.
libease.o:
	@install ease.h ${PREFIX}/include/
	@${CC} ${CFLAGS} ${OBJS} ${SRCS}				# Build our .o file from our .c file using flags
install:
	@echo 'Copying libease.so.0.0.1 -> ${LIBPATH}'
	@install libease.so.0.0.1 ${LIBPATH}				# Copy our library to the correct path
	@ldconfig							# Run ldconfig to install shared library
	@echo 'Linking ${LIBPATH}/libease.so.0.0.1 -> ${LIBPATH}/libease.so'
	@ln -s ${LIBPATH}/libease.so.0.0.1 ${LIBPATH}/libease.so	# Link our access file in
	@echo 'Copying ease.h -> ${PREFIX}/include/'
	@install ease.h ${PREFIX}/include/				# Install the header file
	@echo Done, Please type \'make test\' to ensure that the
	@echo library was installed properly.
uninstall:
	@rm -f ${LIBPATH}/libease*					# Remove all our library files
	@rm -f ${PREFIX}/include/ease.h					# Remove the header file
	@ldconfig							# Clean up our symbols

clean:
	@echo Removing all object files
	@rm -f ${OBJS} libease.so.0.0.1 ease ease.o			# Remove any files from our last build
	@echo Done
test:
	@echo Compiling test executable
	@${CC} ${BINFLAGS} ease.c -o ease.o				# Create our test .o file
	@${CC} -g -o ease ease.o -I/usr/include -L${LIBPATH} -lease	# Link in our library
	@echo Running our test
	@./ease in							# Execute our test
	@./ease	out							# Execute our test
	@./ease io							# Execute our test
	@./ease	oi							# Execute our test
	@./ease	none							# Execute our test
	@echo Done
	@echo If you would like to execute the test manually,
	@echo please run ./ease from within this directory.

