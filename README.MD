# README

This project is targeting on Ubuntu 24. It's must also posibly builded on macos. But seems not suport Windows system (because no support from userver).

## Preparing environments for building

What to need to install in sytem first:

1. Install boost libraries:

    ```sh
        #Before installing Boost, check if it is already installed and its version:
        dpkg -l | grep libboost

        # check avalible version at repository:
        apt-cache policy libboost-dev

        # instal command:
        sudo apt install libboost-all-dev
    ```

2. Install protobuf:

    to erase all files in folder: `rm -rf *`

    Install Protobuf from source:
    
    ```sh
        # clone the repository:
        git clone --recursive https://github.com/protocolbuffers/protobuf.git /tmp/protobuf

        # checkout to defined version (887e95d is commit hash fo c++ version 27.1):
        cd /tmp/protobuf && git checkout 887e95d
        git submodule update --init --recursive

        mkdir cmake/build-debug && cd cmake/build-debug

        # run configuration:
        #cmake -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Debug ../..
        #cmake -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release ../..
        cmake -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local ../..
        
        #cmake --build . 
        make -j$(nproc)
        sudo make install
        sudo ldconfig
        
        # install protobuf:
        sudo make install
        sudo ldconfig

    ```

    Install GRPC from source:

    ```sh
        git clone --recursive https://github.com/grpc/grpc.git /tmp/grpc
        cd /tmp/grpc

        # Checkout desired version (optional)
        # 4795c5e - is hash for commit grpc Release v.1.64.2
        git checkout 4795c5e  # Replace with the desired version
        git submodule update --init --recursive

        # Build gRPC
        mkdir cmake/build && cd cmake/build
        cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local ../..
        make -j$(nproc)
        sudo make install
        sudo ldconfig
    ```

3. Install OpenSSL, Cmake module for Jemalloc and others:

    ```sh
        sudo apt install libssl-dev libyaml-cpp-dev libzstd-dev libjemalloc-dev libnghttp2-dev libev-dev libzstd-dev #libgrpc-dev libgrpc++-dev protobuf-compiler-grpc
    ```

4. Install postresql:

    ```sh
        # Установим недоставющие зависимости
        sudo apt install wget ca-certificates gnupg2 lsb-release

        # Создадим файл конфигурации репозитория
        sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'

        # Скачаем ключ подписи 
        wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -

        # Обновим список пакетов и установим последнюю версию PostgreSQL
        sudo apt-get update && sudo apt-get -y install postgresql

        # Check the instalation:
        service postgresql status
    ```

---
