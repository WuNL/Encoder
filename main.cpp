//
// Created by wunl on 18-8-1.
//

#include <iostream>

#include "httpServer.h"

int main(int argc, char **argv)
{
    int port = 0;
    int numThreads = 0;
    if (argc < 3)
    {
        port = 8000;
        numThreads = 4;
    } else
    {
        port = atoi(argv[1]);
        numThreads = atoi(argv[2]);
    }
    httpServer s(port, numThreads);
    s.start();
}