# This should work on Stampede2

autoreconf -f -i

export PKGPATH=/work/00161/karl/stampede2/public
export CLASSPATH=/work/00161/karl/stampede2/public
export MODULEPATH=$CLASSPATH/ohpc/pub/modulefiles/:$MODULEPATH

# load fixed toolchain
module swap intel gnu7
# verify the correct version: /work/00161/karl/stampede2/public/ohpc/pub/compiler/gcc/7.1.0/bin/gcc
which gcc

# configure 
./configure --with-masa=$PKGPATH/masa-gnu7-0.50 --with-grvy=$PKGPATH/grvy-gnu7-0.34 --enable-coverage 
