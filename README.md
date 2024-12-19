# TCP Client

This repository contains the source code for a simple TCP client that was specifically developed for the coursework.

## How to start

First, you must copy this repository locally to your computer using the following command:

```bash
git clone https://github.com/DmitriyRomanov17/KursovayaTimp.git
```


Next, we need to build our project using the following command:

```bash
make
```
or

```bash
make build

```

After successful build we will have a _client_ file in the directory.
To get help on the client startup command, simply type the following command in a terminal:

```bash
./client 
```

Typically, a program reference looks like this:

```txt
client -a <server_address> -p <server_port> -i <input_file> -o <output_file> -c <config_file>

Options:
  -a address     Server address (required)

  -p port        Server port (optional, default: 33333)
  -i input_file  Input file name (required)
  -o output_file Output file name (required)
  -c config_file Configuration file with LOGIN and PASSWORD (optional, default: ~/.config/client.config)
  -h             Display help
```

In order for our client to work, we need to give it the server address and port.
It is also necessary to create files to store the transmitted values and to store the results received from the server (_input.txt_, _output.bin_).

Example of _input.txt_ file contents:

```txt
1.1 2.2 3.3
1.1 2.2 3.3 4.4
1.1 2.2 3.3 4.4 5.5
```

You can also change the contents of the _client.config_ file that stores user information for authorization.
Example of a configuration file:

```txt
user

P@ssW0rd
```

Then you simply run the program!

Example of launching the program:

```bash

./client -a 127.0.0.1 -p 33333 -i input.txt -o output.bin -c .config/client.config
```

## How to test

If you want to test the client, enter the following command in the terminal:

```bash
make test
```

If everything was successful, you should see the following output in the terminal:

```txt
g++ -std=c++17 -Wall -I/usr/include/UnitTest++ test.cpp -o client_test -L/usr/lib/x86_64-linux-gnu -lUnitTest++
./client_test
Success: 9 tests passed.
Test time: 0.00 seconds.
rm -f client_test
```

Note that we use the UnitTest++ library for testing. Therefore, if the test does not start, it is possible that this library is simply not installed on your device or has an outdated version. To make it work, enter the following command:

```bash
sudo apt update
sudo apt install libunittest++-dev
```

# How to generate documentation

If you want to generate documentation for this client, use the following commands:

```bash
make doc
cd documentation/docs/latex
make
```

If you are getting errors, try installing the following commands:

```bash
sudo apt update
sudo apt install texlive texlive-latex-extra texlive-fonts-recommended
sudo apt-get install texlive-lang-cyrillic
```

The documentation file is called  _refman.pdf_.
