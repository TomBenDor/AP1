# Remote Classifier - TCP \ UDP

## Implementation

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

### The servers

To run both types of servers from the same program, we used the factory design pattern to run each server by the
required protocol. We get both the server protocol and the path to the classified objects via the command line
parameters.

Using the `Socket` interface, we can set the server type at runtime, by initialising the servers we bind their sockets.
Then, they wait for a client (Each server implements that differently), the servers get the data as a string of indices
separated by spaces and new lines. The selected server creates an `Iris` for each set of indices, classifies it using
the `KNNClassifier` from the previous assignment and returns the types.

### The clients

The program creates a `TCPClient` and a `UDPClient` which both connect their matching server. The client uses the
factory design pattern when it gets the selected protocol from the user. Then, the unclassified data is sent to the
server via one of the sockets. The server receives the calculated types and the client writes the output into a csv
file.

## Running

You can run the project using our provided `CMakeLists.txt` file:

**Executing the servers**

```bash
mkdir build-server
cd build-server
cmake ..
make
```

Then execute both servers in two different processes:

```bash
./Server UDP <path-to-classified.csv>
```

```bash
./Server TCP <path-to-classified.csv>
```

**Executing the client**

```bash
mkdir build-client
cd build-client
cmake ..
make
./Client <protocol (UDP \ TCP)> <path-to-unclassified.csv> <path-to-output.csv>
```