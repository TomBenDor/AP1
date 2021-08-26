#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H


class Socket {
public:
    static const int buffer_size = 4096;

    virtual void send(std::string) = 0;

    virtual std::string recv() = 0;

    virtual void close() = 0;

    virtual ~Socket() = default;
};


#endif //CLIENT_SOCKET_H
