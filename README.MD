# README

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

    Debian:

    ```sh
        sudo apt update
        sudo apt install protobuf-compiler python3-protobuf libzstd-dev
    ```

    macOS:

    ```sh
        brew install protobuf
    ```

3. Install OpenSSL, Cmake module for Jemalloc and others:

    ```sh
        sudo apt install libssl-dev
        sudo apt install libyaml-cpp-dev
        sudo apt install libzstd-dev
        sudo apt install libjemalloc-dev
        sudo apt install libnghttp2-dev
        sudo apt install libev-dev
    ```


---
