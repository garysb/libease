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
	@echo "Building ease library"
	@${CC} ${LIBFLAGS},${@:.${EASEVER}=.0} -o $@ ${OBJS} -lc
	@echo "Complete. Please type 'make install' to install."

# Build our .o file from our .c file using flags
libease.o:
	@install --mode=0644 ease.h ${PREFIX}/include/
	@${CC} ${CFLAGS} ${OBJS} ${SRCS}

# Install libease into the system
install:
	@echo "Copying libease.so.${EASEVER} -> ${LIBPATH}"
	@install --mode=0644 libease.so.${EASEVER} ${LIBPATH}
	@ldconfig
	@echo "Linking ${LIBPATH}/libease.so.${EASEVER} -> ${LIBPATH}/libease.so"
	@ln -s ${LIBPATH}/libease.so.${EASEVER} ${LIBPATH}/libease.so
	@echo "Copying ease.h -> ${PREFIX}/include/"
	@install --mode=0644 ease.h ${PREFIX}/include/
	@echo "Installing man libease.3 -> ${MAN_PATH}/libease.3"
	@install --mode=0644 libease.3 $(MAN_PATH)
	@ldconfig
	@echo "Complete. Please type 'make test' to ensure that the\nlibrary was installed properly."

# Uninstall libease from the system
uninstall:
	@echo "Removing library files from ${LIBPATH}/"
	@rm -f ${LIBPATH}/libease*
	@echo "Removing ease.h header file from ${PREFIX}/include/"
	@rm -f ${PREFIX}/include/ease.h
	@ldconfig
	@echo "Complete"

# Clean up the build invironment
clean:
	@echo "Removing all object files"
	@rm -f ${OBJS} libease.so.${EASEVER} ease ease.o
	@echo "Complete"

# Run a test to check libease built correctly
test:
	@echo "Compiling test executable"
	@${CC} ${BINFLAGS} ease.c -o ease.o

	@${CC} -g -o ease ease.o -I/usr/include -L${LIBPATH} -lease

	@echo "Running our tests"
	@./ease none in out io oi bi bo ki ko kb multi
	@echo "Complete"
	@echo "If you would like to execute the test manually,"
	@echo "please run ./ease from within this directory."
