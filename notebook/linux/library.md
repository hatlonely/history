# librarys

## protobuf
https://code.google.com/p/protobuf/

```bash
$ wget https://protobuf.googlecode.com/svn/rc/protobuf-2.5.0.tar.gz 
$ tar -xzvf protobuf-2.5.0.tar.gz
$ cd protobuf-2.5.0.tar.gz
$ ./configure --prefix=<directory>
$ make
$ make install
```

## gtest
https://code.google.com/p/googletest/

```bash
$ wget https://googletest.googlecode.com/files/gtest-1.6.0.zip
$ unzip gtest-1.6.0.zip
$ cd gtest-1.6.0
$ export GTEST_DIR=`pwd`
$ g++ -I${GTEST_DIR}/include -I${GTEST_DIR} -c ${GTEST_DIR}/src/gtest-all.cc
$ ar -rv libgtest.a gtest-all.o
$ cp libgtest.a lib
```

## gmock
https://code.google.com/p/googlemock/

```bash
$ wget https://googletest.googlecode.com/files/gmock-1.6.0.zip
$ unzip gmock-1.6.0
$ cd gmock-1.6.0
$ export GTEST_DIR=`pwd`/gtest
$ export GMOCK_DIR=`pwd`
$ g++ -I${GTEST_DIR}/include -I${GTEST_DIR} -I${GMOCK_DIR}/include \
          -I${GMOCK_DIR} -c ${GTEST_DIR}/src/gtest-all.cc
$ g++ -I${GTEST_DIR}/include -I${GTEST_DIR} -I${GMOCK_DIR}/include \
          -I${GMOCK_DIR} -c ${GMOCK_DIR}/src/gmock-all.cc
$ ar -rv libgmock.a gtest-all.o gmock-all.o
libgmock.a => lib
```

## boost
$ boost_1_56_0.tar.gz
$ tar -xzvf boost_1_56_0.tar.gz
$ cd boost_1_56_0
$ ./bootstrap
$ ./b2
stage/lib => lib
boost => include
