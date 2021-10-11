# Ex3

## Implementation

We designed the code so the client and the server will be separated, it means the client doesn't know what the server is
about to send - all it does is sending messages and receiving messages.

### Communication

The communication between the client and the server uses the following protocol:

```c++
std::string recv(int sock) {
    std::string msg;
    std::string ending = "<end>";

    char buffer[1];
    while (!std::equal(ending.rbegin(), ending.rend(), msg.rbegin())) {
        buffer[0] = 0;
        ssize_t read_bytes = ::recv(sock, buffer, 1, 0);
        if (read_bytes < 0) {
            perror("error writing to sock");
        }
        msg.append(buffer);
    }
    return msg.substr(0, msg.length() - 5);
}

void send(int sock, const std::string &string) {
    std::string msg = string + "<end>";
    //Send the string through the socket
    size_t sent_bytes = ::send(sock, msg.c_str(), strlen(msg.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}
```

This enables us to send unlimited-size messages and keep them separated.

### Multithreading

#### Client

The client has 2 threads:

- Sending thread
- Receiving thread

That way we can keep sending messages without having to wait for response. For example, if we have the following
instructions:

```
1
train.csv
test.csv
3
5
out.csv
6
```

We can send them to the server at once, responses will be printed or saved when arriving, as necessary.

#### Server

The server uses multithreading for two reasons:

- Handling multiple clients simultaneously.
- Handling time-consuming commands on a different thread so the client will be able to send more messages while waiting.

## Running

You can compile & run the project via our provided `CMakeLists.txt` file listed in the ex3 directory.

```bash
mkdir build
cd build
cmake ..
make
```

Then run the server at first:

```bash
cd server
./Server
```

Run each client in a different terminal:

```bash
cd client
./Client
```