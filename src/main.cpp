#include <iostream>
#include <string.h>
#include <lux/index.h>

static void
usage()
{
    std::cout << "usage:" << std::endl;
    std::cout << "  luxcmd init <db>" << std::endl;
}

static int
init(Lux::Engine engine, const char* db, int argc, const char* argv[])
{
    if (!engine.open(db, Lux::DB_CREAT)) {
        std::cerr << "opening engine failed" << std::endl;
        return 1;
    }
    return 0;
}

int
main(int argc, const char* argv[])
{
    if (argc < 3) {
        usage();
        return 1;
    }

    const char* db = argv[2];
    Lux::Config::Document config;
    if (!Lux::DocumentConfigParser::parse(db, config)) {
        std::cerr << "parse failed - " << db << std::endl;
        return 1;
    }
    Lux::Engine engine(config);

    const char* cmd = argv[1];
    if (strcmp(cmd, "init") == 0) {
        return init(engine, db, argc - 4, argv + 4);
    }

    return 0;
}

// vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4
