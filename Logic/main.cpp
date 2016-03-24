#include "program_logic.h"

int main(int argc, char *argv[])
{
    ProgramLogic *pl = new ProgramLogic;

    pl->set_start_url("https://curl.haxx.se/libcurl/");
    pl->set_start_url("libcurl is a free and ");

    pl->start();
    return 0;
}
