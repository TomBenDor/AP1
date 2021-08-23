#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H


class Server {
public:
    static const int buffer_size = 4096;

    virtual void send(std::string) = 0;

    virtual std::string recv() = 0;

    virtual void close() = 0;
};


#endif //CLIENT_SERVER_H
