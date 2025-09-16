#include "CppUtilities.hpp"
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <filesystem>

#if 0
./test2.exe -f bin2format/commdata.txt '/[TR]x/' 's/^[TR]x://' 'p/^(.*)\-[^\-]+/$1: /' 's/^.*\-([^\-]+$)/$1/' '/^010400/:h2 WW h2' '/^01044C/:h3 h4h4FFFFFFFFFFVVVF h2'
#endif

static const char Revision[] = "0.08.04";

static void printRevision(void)
{
    std::cout << "Binary to Format value converter: Revision " << Revision << std::endl;
}

static void printHelp(boost::program_options::options_description & desc)
{
    printRevision();
    std::cout << desc << std::endl;
    std::cout << "Format" << std::endl;
    std::cout << "    c :  8 bit signed value"   << std::endl;
    std::cout << "    b :  8 bit unsigned value" << std::endl;
    std::cout << "    s : 16 bit signed value"   << std::endl;
    std::cout << "    w : 16 bit unsigned value" << std::endl;
    std::cout << "    i : 32 bit signed value"   << std::endl;
    std::cout << "    d : 32 bit unsigned value" << std::endl;
    std::cout << "    j : 64 bit signed value"   << std::endl;
    std::cout << "    q : 64 bit unsigned value" << std::endl;
    std::cout << "    f : float"                 << std::endl;
    std::cout << "    v : double"                << std::endl;
    std::cout << "    a*: ascii data          ex) 313233 -> a3 -> '123'"    << std::endl;
    std::cout << "    h*: hex data            ex) 313233 -> h3 -> '313233'" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "    cbswidjqfvah: little endien  0001 -> w -> 256" << std::endl;
    std::cout << "      SWIDJQFVAH: Big endien     0001 -> W ->  1" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Usag:" << std::endl;
    std::cout << "  # ./bin2format.exe --file modbus.log '/^[RT]x/' 's/^[RT]x:.*-//' '^010400:bbWWH2' '^01044C:bbbVVFWDH2'" << std::endl;
    std::cout << "  # echo '00010102' | ./bin2format.exe 'Wh2'                -> 1, 0102"   << std::endl;
    std::cout << "  # echo '00010102' | ./bin2format.exe 'wH2'                -> 256, 0201" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  # echo '1, 7.0' | ./bin2format.exe -m csv 'bF'            -> 0140E00000" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  # echo '1, 7.0' | ./bin2format.exe -m csv 'bF |  ./bin2format.exe -m out -f test.bin" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '0:h16'          -> 00000000h: xx..." << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '0000h:h16'      -> 00000000h: xx..." << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '0000h:h16:4'    -> 00000000h: xx..." << std::endl;
    std::cout << "                                                               00000010h: xx..." << std::endl;
    std::cout << "                                                                   ..."          << std::endl;
    std::cout << "                                                               00000030h: xx..." << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '00.0h:h16'      -> 00000000h: xx..." << std::endl;
    std::cout << "                                                               00000010h: xx..." << std::endl;
    std::cout << "                                                                   ..."          << std::endl;
    std::cout << "                                                               000000F0h: xx..." << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '00[01]0h:h16'   -> 00000000h: xx..." << std::endl;
    std::cout << "                                                               00000010h: xx..." << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '00[0-4]0h:h16'  -> 00000000h: xx..." << std::endl;
    std::cout << "                                                               00000010h: xx..." << std::endl;
    std::cout << "                                                                   ..."          << std::endl;
    std::cout << "                                                               00000040h: xx..." << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f test.bin '10{3}h:h16'     -> 00001000h: xx..." << std::endl;
}

class BinaryConverter
{
    class ArgItem
    {
    public:
        size_t          cmd;
        std::regex      reg;
        std::string     str;
        ArgItem(void)                                                   : cmd(-1), reg(""), str("") { }
        ArgItem(size_t c, const std::string & r, const std::string & s) : cmd(c),  reg(r),  str(s)  { }
    };
private:
    bool f_dump    = false;
    bool f_addr    = false;
    std::list<ArgItem> args;
    BinaryControl   bin;
public:
    BinaryConverter(void) {}
    virtual ~BinaryConverter(void) {}
    void set_dump(bool flag)          { f_dump  = flag; }
    void set_print_address(bool flag) { f_addr  = flag; }
    void set_arg(const std::string & str)
    {
        CppRegexp reg_arg({ "^/(.*)/$", "^s/(.*)/([^/]*)/$", "^p/(.*)/([^/]*)/$", "^/(.*)/:([0-9cbswidjqfvSWIDJQFVaAhH ]+)$", "^[0-9cbswidjqfvSWIDJQFVaAhH ]+$" });
        size_t cmd = reg_arg.select(str);
        std::vector<std::function<void()>> act =
        {
            /* 0: grep      */ [&]() { std::string reg = reg_arg.replace(cmd, str, "$1");                                                    ArgItem arg(cmd, reg, str); args.push_back(arg); },
            /* 1: reprace   */ [&]() { std::string reg = reg_arg.replace(cmd, str, "$1"); std::string rep = reg_arg.replace(cmd, str, "$2"); ArgItem arg(cmd, reg, rep); args.push_back(arg); },
            /* 2: print     */ [&]() { std::string reg = reg_arg.replace(cmd, str, "$1"); std::string rep = reg_arg.replace(cmd, str, "$2"); ArgItem arg(cmd, reg, rep); args.push_back(arg); },
            /* 3: pattern   */ [&]() { std::string reg = reg_arg.replace(cmd, str, "$1"); std::string fmt = reg_arg.replace(cmd, str, "$2"); ArgItem arg(cmd, reg, fmt); args.push_back(arg); },
            /* 4: default   */ [&]() { std::string reg(".");                                                                                 ArgItem arg(cmd, reg, str); args.push_back(arg); }
        };
        if(cmd < act.size()) { (act[cmd])(); }
    }
    size_t arg_size(void) const { return args.size(); }
    void print(std::vector<ClsValue> list)
    {
        if(0 < list.size())
        {
            size_t idx = 0, tail = list.size() - 1;
            for(auto & v : list)
            {
#if 0
                if(ClsValue::type_str == v.get_type())  { std::cout << "\"" << v.str() << "\""; }
                else                                    { std::cout << v.str(); }
#endif
                std::cout << v.str();
                if(idx != tail) { std::cout << ", "; }
                idx ++;
            }
        }
    }

    //---------------------------------------------------------------------------------------------------------------------
    void convert(const std::string & org)
    {
        std::string str(org);
        BinaryControl bin;
        bool f_print = true;
        bool f_loop  = true;
        bool f_print_csv = false;
        std::vector<std::function<void(ArgItem &)>> act =
        {
            /* 0: grep      */ [&](ArgItem & cmd) { if(std::regex_search(str, cmd.reg)) { f_print = true; } else { f_print = false; f_loop = false; } },
            /* 1: reprace   */ [&](ArgItem & cmd) { if(std::regex_search(str, cmd.reg)) { f_print = true; str = std::regex_replace(str, cmd.reg, cmd.str); } },
            /* 2: print     */ [&](ArgItem & cmd)
            {
                f_print = true;
                if(std::regex_search(str, cmd.reg)) { std::cout << std::regex_replace(str, cmd.reg, cmd.str); }
                else                                { std::cout << str; }
            },
            /* 3: pattern   */ [&](ArgItem & cmd) { },
            /* 4: default   */ [&](ArgItem & cmd) {}
        };
        std::vector<std::function<void(ArgItem &)>> act2 =
        {
            /* 0: grep      */ [&](ArgItem & cmd) { },
            /* 1: reprace   */ [&](ArgItem & cmd) { },
            /* 2: print     */ [&](ArgItem & cmd) { },
            /* 3: pattern   */ [&](ArgItem & cmd)
            {
                    std::string hex = bin.dump();
                    if(std::regex_search(hex, cmd.reg))
                    {
                        f_print = false;
                        if(f_dump) { std::cout << ", "; }
                        if(f_print_csv) { std::cout << ", "; }
                        print(bin.get(cmd.str));
                        f_print_csv = true;
                    }
            },
            /* 4: default   */ [&](ArgItem & cmd)
            {
                    f_print = false;
                    if(f_dump) { std::cout << ", "; }
                    if(f_print_csv) { std::cout << ", "; }
                    print(bin.get(cmd.str));
                    f_print_csv = true;
            }
        };
        for(auto & cmd : args)
        {
            if(!f_loop) break;
            if(cmd.cmd < act.size()) { (act[cmd.cmd])(cmd); }
        }
        if(f_print)
        {
            { BinaryControl temp(str); bin.swap(temp); }
            if(f_dump) { std::cout << bin.dump(); f_print = false; }
            for(auto & cmd : args)
            {
                bin.set_pos(0);
                if(cmd.cmd < act2.size()) { (act2[cmd.cmd])(cmd); }
            }
            if(f_print) { std::cout << str; }
            std::cout << std::endl;
        }
    }
    //---------------------------------------------------------------------------------------------------------------------
    void loadBinary(const std::string & fname)
    {
        BinaryControl temp(fname, 1);
        bin.swap(temp);
    }
    void print_bin(const std::string & str)
    {
        CppRegexp reg_cmd({
                "^([0-9]+):([^:]+)$",
                "^([0-9]+):([^:]+):([0-9]+)$",

                "^([0-9a-fA-F \\[\\]\\-\\.\\{\\}]+)h:([^:]+)$",
                "^([0-9a-fA-F \\[\\]\\-\\.\\{\\}]+)h:([^:]+):([0-9]+)$",

                "^/([0-9a-fA-F \\[\\]\\-\\.\\{\\}]+)/:([^:]+)$",
                "^([0-9]+):/([0-9a-fA-F \\[\\]\\-\\.\\{\\}]+)/:([^:]+)$",
                "^([0-9a-fA-F \\[\\]\\-\\.\\{\\}]+)h:/([0-9a-fA-F \\[\\]\\-\\.\\{\\}]+)/:([^:]+)$" });
        auto idx = reg_cmd.select(str);
        std::list<size_t> list_addr;
        size_t count = 1;
        std::string addr;
        std::string fmt("");
        std::string find("");
        std::vector<std::function<void()>> act =
        {
            /* 0: */ [&]() { addr = reg_cmd.replace(idx, str, "$1"); list_addr.push_back(stoi(addr));     fmt  = reg_cmd.replace(idx, str, "$2"); },
            /* 1: */ [&]() { addr = reg_cmd.replace(idx, str, "$1"); list_addr.push_back(stoi(addr));     fmt  = reg_cmd.replace(idx, str, "$2"); auto n(reg_cmd.replace(idx, str, "$3")); count = stoi(n); },

            /* 2: */ [&]() { addr = reg_cmd.replace(idx, str, "$1"); list_addr = bin.toAddressList(addr); fmt  = reg_cmd.replace(idx, str, "$2"); },
            /* 3: */ [&]() { addr = reg_cmd.replace(idx, str, "$1"); list_addr = bin.toAddressList(addr); fmt  = reg_cmd.replace(idx, str, "$2"); auto n(reg_cmd.replace(idx, str, "$3")); count = stoi(n); },

            /* 4: */ [&]() { list_addr.push_back(0);                                                      find = reg_cmd.replace(idx, str, "$1"); fmt = reg_cmd.replace(idx, str, "$2"); },
            /* 5: */ [&]() { addr = reg_cmd.replace(idx, str, "$1"); list_addr.push_back(stoi(addr));     find = reg_cmd.replace(idx, str, "$2"); fmt = reg_cmd.replace(idx, str, "$3"); },
            /* 6: */ [&]() { addr = reg_cmd.replace(idx, str, "$1"); list_addr = bin.toAddressList(addr); find = reg_cmd.replace(idx, str, "$2"); fmt = reg_cmd.replace(idx, str, "$3"); }
        };
        if(idx < act.size())
        {
            (act[idx])();
            if(idx < 4)
            {
                for(auto & addr : list_addr)
                {
                    bin.set_pos(addr);
                    for(size_t cnt=0; cnt < count; cnt++)
                    {
                        if(f_addr) { printf("%08lX: ", bin.get_pos()); }
                        print(bin.get(fmt));
                        printf("\n");
                    }
                }
                return;
            } else { }
        }
    }
    //---------------------------------------------------------------------------------------------------------------------
    void print_csv(std::string & org)
    {
        std::string str(org);
        bool f_print = true;
        bool f_loop  = true;
        BinaryControl bin;
        std::vector<std::function<void(ArgItem &)>> act =
        {
            /* 0: grep      */ [&](ArgItem & cmd) { if(std::regex_search(str, cmd.reg)) { f_print = true; } else { f_print = false; f_loop = false; }        },
            /* 1: reprace   */ [&](ArgItem & cmd) { if(std::regex_search(str, cmd.reg)) { f_print = true; str = std::regex_replace(str, cmd.reg, cmd.str); } },
            /* 2: print     */ [&](ArgItem & cmd) { },
            /* 3: pattern   */ [&](ArgItem & cmd) { },
            /* 4: default   */ [&](ArgItem & cmd)
            {
                f_print = false;
                f_loop  = false;

                std::list<std::string> list;
                boost::tokenizer< boost::escaped_list_separator< char > > tokens(str);
                for(auto & token : tokens) { list.push_back(token); }
                bin.set(list, cmd.str);
                std::cout << bin.dump();
            }
        };
        for(auto & cmd : args) { if(!f_loop) break; if(cmd.cmd < 3) { (act[cmd.cmd])(cmd); } }
        if(f_print)
        {
            for(auto & cmd : args)
            {
                if(!f_loop) break;
                if(cmd.cmd == 4) { (act[cmd.cmd])(cmd); break; }
            }
            if(f_print) { std::cout << str; }
            std::cout << std::endl;
        }
    }

    //---------------------------------------------------------------------------------------------------------------------
    void in(std::string & str)
    {
        BinaryControl temp(str);
        bin += temp;
    }
    void output(std::string & fname)
    {
        std::ofstream ofs(fname, std::ios::binary);
        if(ofs)
        {
            ofs.write(reinterpret_cast<const char *>(bin.data()), bin.size());
        } else { std::cout << "Fail of file open: " << fname << std::endl; }
    }
};

int main(int argc, char * argv[])
{
    try
    {
        boost::program_options::options_description desc("bin2format.exe [Options] arg");
        desc.add_options()
            ("file,f",       boost::program_options::value<std::string>(),                          "file name"                                             )
            ("mode,m",       boost::program_options::value<std::string>()->default_value("conv"),   "select mode: [conv, bin, csv, out]"                    )
            ("print-address,a",                                                                     "print address"                                         )
            ("dump,d",                                                                              "print binary dump"                                     )
            ("version,v",                                                                           "Print version"                                         )
            ("help,h",                                                                              "help"                                                  );
        boost::program_options::variables_map argmap;
        auto const parsing_result = parse_command_line(argc, argv, desc);
        store(parsing_result, argmap);
        notify(argmap);

        if(argmap.count("version")) { printRevision(); return (0); }
        if(argmap.count("help"))    { printHelp(desc); return (0); }

        BinaryConverter bin;
        if(argmap.count("dump"))            { bin.set_dump(true);          }
        if(argmap.count("print-address"))   { bin.set_print_address(true); }
        for(auto const & str : collect_unrecognized(parsing_result.options, boost::program_options::include_positional)) { bin.set_arg(str); }

        if(argmap.count("mode"))
        {
            CppRegexp reg_mode({ "^conv$", "^bin$", "^csv$", "^out$"});
            auto mode = reg_mode.select(argmap["mode"].as<std::string>());
            auto mode_conv = [&]()
            {   /* format convert mode */
                if(0 < bin.arg_size())
                {
                    std::string str;
                    if(argmap.count("file"))
                    {
                        auto fname = argmap["file"].as<std::string>();
                        if(std::filesystem::exists(fname))
                        {
                            std::ifstream ifs(fname);
                            while(std::getline(ifs,str)) { bin.convert(str); }
                        } else { std::cout << "file not found: " << fname << std::endl; }
                    } else { while(std::getline(std::cin, str)) { bin.convert(str); } }
                } else { printHelp(desc); }
            };
            auto mode_bin = [&]()
            {   /* binary mode */
                if(argmap.count("file"))
                {
                    auto fname = argmap["file"].as<std::string>();
                    if(std::filesystem::exists(fname))
                    {
                        bin.loadBinary(fname);
                        auto flag_cin =true;
                        for(auto const & str : collect_unrecognized(parsing_result.options, boost::program_options::include_positional))
                        {
                            flag_cin = false;
                            bin.print_bin(str);
                        }
                        if(flag_cin)
                        {
                            std::string str;
                            while(std::getline(std::cin, str))
                            {
                                if(str == "end") { break; }
                                bin.print_bin(str);
                            }
                        }
                    } else { std::cout << "file not found: " << fname << std::endl; }
                }
            };
            auto mode_csv = [&]()
            {   /* csv mode */
                std::string str;
                str.clear();
                if(0 < bin.arg_size())
                {
                    if(argmap.count("file"))
                    {
                        auto fname = argmap["file"].as<std::string>();
                        if(std::filesystem::exists(fname))
                        {
                            std::ifstream ifs(fname);
                            while(std::getline(ifs,str)) { bin.print_csv(str); }
                        } else { std::cout << "file not found: " << fname << std::endl; }
                    } else { while(std::getline(std::cin, str)) { bin.print_csv(str); } }
                } else { std::cout << "not first argment: first argment is csv format" << std::endl; }
            };
            auto mode_out = [&]()
            {   /* output mode */
                std::string str;
                if(argmap.count("file"))
                {
                    auto fname = argmap["file"].as<std::string>();
                    while(std::getline(std::cin, str)) { bin.in(str); }
                    bin.output(fname);
                }
            };
            std::vector<std::function<void()>> act = { mode_conv, mode_bin, mode_csv, mode_out };
            if(mode < act.size()) { (act[mode])(); }
        } else { printHelp(desc); }
    }
    catch(const std::exception & e) { std::cout << "exeption: "       << e.what() << std::endl; return -2; }
    catch(...)                      { std::cout << "unknown exeption"             << std::endl; return -3; }
    return 0;
}
