# Server\Client - TCP\UDP

# Implementation

We used an interface called `Socket` to make the code polymorphic:

```c++
class Socket {
    static const int buffer_size = 4096;
    virtual void send(std::string) = 0;
    virtual std::string recv() = 0;
    virtual void close() = 0;
    virtual ~Socket() = default;
};
```

We created 4 classes that implement `Socket`: `TCPServer`, `TCPServer`,`UDPServer` and `UDPClient`.

## The servers

In order to run both types of servers from the same program, we used the factory design pattern, in order to run each
server, the user types its type, i.e. TCP or UDP, as the second argument in the command line (the first being the
directory of the classified data).

Then, using the `Socket` interface, we can set the server type at runtime, the servers bind their sockets in the
constructor. Then, they wait for a client (Each server implements that differently), the servers get the data as a
string of indices seperated by spaces and new lines. the server creates an `Iris` for each set of indices, classifies it
using the `KNNClassifier` from the first assignment and returns the types.

## The clients

The clients also use the factory design pattern because they need to be set at runtime. The program creates a
`TCPClient` and a `UDPClient`, when a type is chosen, the client reads the unclassified data from the provided
directory, sends it to the server, receives the calculated types and writes them to the directory of the new file.

## Running