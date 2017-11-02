
// cl /std:c++latest /EHsc /W4 rcygacl.cpp

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;
using namespace std::experimental::filesystem::v1;  

void usage()
{
    cout << "Usage: rcygacl [--help] [file]\n";
    cout << "Repair the broken access control lists of cygwin files.\n";
}

void repair_file(path const & fn)
{
    /*
    Repair by copying.  The program is a Windows program, so the ACL of
    the new file will be correct.  As long as we can read and remove the
    source file, this repair will work.

    Caveat: may use lots of space and time if the file is big.

    An alternate solution would be to "touch" a new temp file, use
    icacls to save the permissions of that and then restore those
    permissions to the target file. The technique implies a rewriting of
    the saved permission file.  And if the target file in a really bad
    shape the process might need administrator access.
    */

    int c = 0;
    path to;
    for(;;)
    {
        ostringstream os; os << c;
        to = fn;
        to += os.str();
        if( !exists(to) ) break;
        ++c;
        if( c >= 1'000'000 )
        {
            throw runtime_error("cannot find a temporary filename");
        }
    }

    rename(fn, to);
    copy(to, fn);
    remove(to);
}

int main(int argc, char ** argv)
{
    if( argc < 2 )
    {
        usage();
        exit(1);
    }

    if( argc == 2  )
    {
        bool is_help = argv[1] == "--help"s ||
                       argv[1] == "-h"s;

        if( is_help )
        {
            usage();
            exit(0);
        }
    }

    try
    {
        char ** beg = argv+1;
        char ** end = argv+argc;
        for( char ** it = beg; it != end; ++it )
        {
            repair_file(*it);
        }
    }
    catch(exception const & ex)
    {
        cerr << ex.what() << '\n';
    }

	return 0;
}
