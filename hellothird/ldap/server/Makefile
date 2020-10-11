WORKROOT=$$(pwd)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
install: berkeleydb
	mkdir -p source && mkdir -p output && cd source && \
	wget ftp://ftp.openldap.org/pub/OpenLDAP/openldap-release/openldap-2.4.47.tgz && \
	gunzip -c openldap-2.4.47.tgz | tar xvfB - && \
	cd openldap-2.4.47 && \
	./configure --prefix=${WORKROOT}/output/openldap-2.4.47 && make depend && make -j16 && make install
	
berkeleydb: 
	mkdir -p source && mkdir -p output && cd source && \
	wget http://anduin.linuxfromscratch.org/BLFS/bdb/db-5.3.28.tar.gz && \
	tar -xzvf db-5.3.28.tar.gz && \
	cd db-5.3.28 && sed -i "" 's/\(__atomic_compare_exchange\)/\1_db/' src/dbinc/atomic.h && \
	cd build_unix && ../dist/configure --prefix=/usr \
					--enable-compat185 \
					--enable-dbm \
					--disable-static \
					--enable-cxx && \
	make -j16 && sudo make install	
endif

ifeq ($(UNAME_S), Linux)
install:
	# sudo yum install libdb-devel -y
	mkdir -p source && mkdir -p output && cd source && \
	wget ftp://ftp.openldap.org/pub/OpenLDAP/openldap-release/openldap-2.4.47.tgz && \
	gunzip -c openldap-2.4.47.tgz | tar xvfB - && \
	cd openldap-2.4.47 && \
	./configure --prefix=${WORKROOT}/output/openldap-2.4.47 && make depend && make -j16 && make install
endif

run:
	cd output/openldap-2.4.47 && ./libexec/slapd

