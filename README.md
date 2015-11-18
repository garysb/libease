# libease installation guide #

Depending on how you get libease, there are two diferent installation methods.
With the version checked out from the subversion repository, you will need to
have the automake tools installed. With the tar.gz file from sourceforge or from
freashmeat, this has already been done for you.

As most people that are less savvy tend to stick to Ubuntu, I will describe the
installation methods for Ubuntu. Please bare this in mind and change commands to
match your environment.

### 1. USING THE CHECKED OUT VERSION FROM svn.stroppytux.net ###
   *  If you downloaded the tar.gz version, skip to section 2.
   *  # sudo apt-get install automake libtool build-essential
   *  # svn co http://anonymous@svn.stroppytux.net/libease/tags/0.0.6 libease-0.0.6
   *  Change into the root directory of libease (contains configure.ac)
   *  # libtoolize # (glibtoolize in OSX) This generates the lt-main.sh script for libtool.
   *  # aclocal # This generates your aclocal.m4 file.
   *  # autoheader # This generates the src/config.h.in template file.
   *  # automake --add-missing # This generates all the scripts for autoconf.
   *  # autoconf # This generates your configure script to compile libease.

### 2. USING THE tar.gz VERSION FROM sourcefore.net/freshmeat.net ###
   *  If you downloaded the subversion version, skip to section 3.
   *  # sudo apt-get install build-essential
   *  # cd /tmp # Change to temp directory. (Should be /usr/src but need to be root for that)
   *  # wget http://downloads.sourceforge.net/project/libease/libease/libease-0.0.6/libease-0.0.6.tar.bz2
   *  # tar -jxf libease-0.0.6.tar.bz2 # Extract the contents (-j: bzip2 -x: extract -f: file)
   *  # cd libease-0.0.6 # Change into the libease source directory.

### 3. ALL USERS ONCE YOU HAVE COMPLETED SECTION 2 OR 3 ###
   *  # ./configure --help # Check which options you need. I use --prefix=/usr
   *  # ./configure <OPTIONS> # configure libease with your options.
   *  # make # Builds libease source into a binary file.
   *  # sudo make install # Installs libease, the header, and the man file.
   *  # sudo ldconfig # Updates the dynamic library listing in your computer.
