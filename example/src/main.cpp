#include <iostream> // std::cout and std::endl
#include <cstring> // std::atoi

#include <mcstatus/mcstatus.hpp>
#include <mcstatus/color.hpp>

// Show usage
void usage()
{
    std::cout <<
        "Usage: ./mcstatus --host <host> --port <port>" << std::endl <<
        "Example ./mcstatus -h 127.0.0.1 -p 25565" <<
    std::endl;
    exit(1);
}

int main(int argc, char** argv)
{
    if (!argc) usage(); // No parameters

    // Server's ip(v4) and port
    std::string hostname;
    uint16_t port;

    // Process the command-line parameters
    int opt_idx = 1;
    for (; opt_idx < argc; opt_idx++)
    {
        if (!*argv[opt_idx] =='-')
            break;

        if (!strcmp(argv[opt_idx], "--host") ||
            !strcmp(argv[opt_idx], "-h"))
        {
            ++opt_idx;
            hostname = argv[opt_idx];
        }
        else if (
            !strcmp(argv[opt_idx], "--port")||
            !strcmp(argv[opt_idx], "-p"))
        {
            ++opt_idx;
            port = static_cast<uint16_t> (std::atoi(argv[opt_idx]));
        }
        else
        {
            fprintf(stderr, "Unknown commandline flag: %s\n", argv[opt_idx]);
            usage();
        }
    }

    if (argc - opt_idx != 0) usage(); // no zuo no die XD

    // Get the motd
    mc::status motd(hostname, port);
    mc::motd_t m = motd.getMotd();
    // Format: player_online/player_max
    std::cout 
        << "players: "
        << m.player_online
        << "/"
        << m.player_max 
        << std::endl;

    // to UNIX-CONSOLE-COLOR.
    std::cout << mc::color(m.description).toString() << std::endl;
    
    return 0;
}
