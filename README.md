# Design FTP Client 


## Setup

### The first:
- Download and install cmake: [download](https://cmake.org/download).
- Download and install tdm-gcc: [download](https://jmeubank.github.io/tdm-gcc/download/) with version ```tdm64-gcc-9.2.0.exe```
or ``` tdm-gcc-9.2.0.exe``` if you use to os 32bit

### The second:

- run Cmake(cmake-gui)

    Step 1: In field **Where is the source code** click **Browser Source...** and select folder `design-ftp-client`
    
    Step 2: Create folder **build** in folder `design-ftp-client`

    Step 3: In field **Where to build the binaries** click **Browser Build...** and select folder `design-ftp-client/build`

    Step 4: After click to **Generate** if have show dialog then select **MinGW Makefiles** and click **Use default native compilers**

### The third:

Step 1: open **cmd** in folder `design-ftp-client/build` (you can view [tutorial](https://www.youtube.com/watch?v=bgSSJQolR0E))

Step 2 : in **cmd** you type
```bash
cmake --build .
ftpclient
```
## Note

After completing the installation steps, from now on every time we want to run the program just open the `compiler.bat` file.