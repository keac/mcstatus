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
    if (argc == true) usage(); // No parameters

    // Server's ip(v4) and port
    std::string hostname;
    uint16_t port = 25565;

    // Process the command-line parameters
    int opt_idx = 1;
    for (; opt_idx < argc; opt_idx++)
    {
        if (*argv[opt_idx] !='-')
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

    mc::status* motd;
    mc::motd_t m;

    // Get the motd
    boost::system::error_code ec;
    motd = new mc::status(hostname, port, ec);
    m = motd->requestMotd();
    if (ec != 0)
    {
        // failed to get motd...
        // reference: https://stackoverflow.com/questions/21046742/using-boostsystemerror-code-in-c
        fprintf(stderr, "server is down\n");
        return 1;
    }
    

    // Outputting to console
    mc::color(m.description).output();

    // e.g "3/100"
    printf("%d/%d\n", m.players_online, m.players_max);

    // Ping
    std::cout << "Ping(ms): " << m.ping << std::endl;

    std::cout << "Kernel: " << m.kernel << std::endl;
    std::cout << "Protocol: " << m.protocol << std::endl;
    //std::cout << "Server ICON: " << m.favicon << std::endl; // base64ed image
    
    delete motd;
    
}
