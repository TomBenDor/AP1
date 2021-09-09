#include "string"

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H


class Socket {
public:
    //Set the buffer size
    static const int buffer_size = 4096;

    /**
     * Send the message through the socket
     */
    virtual void send(std::string) = 0;

    /**
     * Get the message in the socket
     * @return the message
     */
    virtual std::string recv() = 0;

    /**
     * Close the socket
     */
    virtual void close() = 0;

    /**
     * Destructor
     */
    virtual ~Socket() = default;
};


#endif //CLIENT_SOCKET_H
