#include <iostream>
#include <string.h>
#include <lux/index.h>
#include <lux/types.h>

static void
usage()
{
    std::cout << "usage:" << std::endl;
    std::cout << "  luxcmd init db" << std::endl;
    std::cout << "  luxcmd put db id [attr=value]...." << std::endl;
}

static bool
open_db(Lux::Engine engine, const char* path, Lux::db_flags_t oflags=Lux::DB_RDWR)
{
    if (!engine.open(path, oflags)) {
        std::cerr << "opening engine failed - " << path << std::endl;
        return false;
    }
    return true;
}

static int
init(Lux::Engine engine, const char* db, int argc, char* argv[])
{
    return open_db(engine, db, Lux::DB_CREAT) ? 0 : 1;
}

static int
put(Lux::Engine engine, const char* db, int argc, char* argv[])
{
    if (!open_db(engine, db)) {
        return 1;
    }

    Lux::Indexer indexer(engine);
    Lux::Document doc(argv[0]);
    int i;
    for (i = 1; i < argc; i++) {
        char* pair = strdupa(argv[i]);
        char* pc = strchr(pair, '=');
        const char* val;
        if (pc != NULL) {
            *pc = '\0';
            val = pc + 1;
        }
        else {
            val = &pair[strlen(pair)];
        }
        const char* key = pair;
        doc.add(Lux::Field::create(key, val));
    }
    indexer.add(doc);

    return 0;
}

int
main(int argc, char* argv[])
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
    if (strcmp(cmd, "put") == 0) {
        return put(engine, db, argc - 4, argv + 4);
    }

    return 0;
}

// vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4
