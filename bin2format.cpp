#include "CppUtilities.hpp"
#include <boost/program_options.hpp>
#include <fstream>
#include <filesystem>

static const char Revision[] = "0.08.02";

static void printRevision(void)
{
    std::cout << "Binary to Format value converter: Revision " << Revision << std::endl;
}

static void printHelp(boost::program_options::options_description & desc)
{
    printRevision();
    std::cout << desc << std::endl;
    std::cout << "Usag:" << std::endl;
    std::cout << "  # ./bin2format.exe --file modbus.log --grep '^[RT]x:.*-..' --replace '^[RT]x:.*-(..)/$1' '^010400:bbWWH2' '^01044C:bbbVVFWDH2'" << std::endl;
    std::cout << "  # echo '00010102' | ./bin2format.exe '^.:WH2'  -> 1, 0102"   << std::endl;
    std::cout << "  # echo '00010102' | ./bin2format.exe '^.:wh2'  -> 256, 0201" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '0:h16'          -> 00000000h: xx... " << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '0000h:h16'      -> 00000000h: xx... " << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '0000h:h16:4'    -> 00000000h: xx... " << std::endl;
    std::cout << "                                                                     00000010h: xx... " << std::endl;
    std::cout << "                                                                         ... "          << std::endl;
    std::cout << "                                                                     00000030h: xx... " << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '00.0h:h16'      -> 00000000h: xx... " << std::endl;
    std::cout << "                                                                     00000010h: xx... " << std::endl;
    std::cout << "                                                                         ... "          << std::endl;
    std::cout << "                                                                     000000F0h: xx... " << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '00[01]0h:h16'   -> 00000000h: xx... " << std::endl;
    std::cout << "                                                                     00000010h: xx... " << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '00[0-4]0h:h16'  -> 00000000h: xx... " << std::endl;
    std::cout << "                                                                     00000010h: xx... " << std::endl;
    std::cout << "                                                                         ... "          << std::endl;
    std::cout << "                                                                     00000040h: xx... " << std::endl;
    std::cout << "  # ./bin2format.exe -m bin -a -f bin2format.exe '10{3}h:h16'     -> 00001000h: xx... " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Format" << std::endl;
    std::cout << "    c :  8 bit signed value  " << std::endl;
    std::cout << "    b :  8 bit unsigned value" << std::endl;
    std::cout << "    s : 16 bit signed value  " << std::endl;
    std::cout << "    w : 16 bit unsigned value" << std::endl;
    std::cout << "    i : 32 bit signed value  " << std::endl;
    std::cout << "    d : 32 bit unsigned value" << std::endl;
    std::cout << "    j : 64 bit signed value  " << std::endl;
    std::cout << "    q : 64 bit unsigned value" << std::endl;
    std::cout << "    f : float                " << std::endl;
    std::cout << "    v : double               " << std::endl;
    std::cout << "    a*: ascii data          ex) 313233 -> a3 -> '123'   " << std::endl;
    std::cout << "    h*: hex data            ex) 313233 -> h3 -> '313233'" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "    cbswidjqfvah: little endien  0001 -> w -> 256" << std::endl;
    std::cout << "      SWIDJQFVAH: Big endien     0001 -> W ->  1" << std::endl;
#if 0
// # ./test2.exe -b test2.exe '/123[0-f] 00{4} /:h64'                  -> data 検索後にダンプする。
// # ./test2.exe -b test2.exe '0100h:/12 [a-f][a-f] 00{4} /:h32'       -> 0000h から data 検索後にダンブする。
// # ./test2.exe -b test2.exe '0100h:/12 [00, 01, 02, 10~1f, 3.]{4} 00{4} /:h32'       -> 0000h から data 検索後にダンブする。
#endif
}

class BinaryConverter
{
private:
    bool f_addr    = false;
    bool f_dump    = false;
    bool f_pgrep   = false;
    bool f_presp   = false;
    bool f_grep    = false;
    bool f_replace = false;
    std::string     grep_str;
    std::string     replace_str;
    std::regex      reg_grep;
    std::regex      reg_replace;
    std::string     rep_str;
    std::map<std::string, std::regex>  fmt_reg;
    std::map<std::string, std::string> fmt;

    BinaryControl   bin;

public:
    BinaryConverter(void) {}
    virtual ~BinaryConverter(void) {}
    void set_print_address(bool flag) { f_addr  = flag; }
    void set_dump(bool flag)          { f_dump  = flag; }
    void set_print_grep(bool flag)    { f_pgrep = flag; }
    void set_print_replace(bool flag) { f_presp = flag; }
    void set_grep(std::string & str)
    {
        f_grep = true;
        grep_str = str;
        std::regex temp(grep_str);
        reg_grep = temp;
    }
    void set_replace(std::string & str)
    {
        f_replace = true;
        replace_str = str;
        std::regex reg("^(.*)/([^/]*)$");
        std::regex temp(std::regex_replace(str, reg, "$1"));
        reg_replace = temp;
        rep_str = std::regex_replace(str, reg, "$2");
    }
    bool is_print(void) { return (f_pgrep ? true : (f_presp ? true : false)); }
    size_t size(void) { return fmt_reg.size(); }
    void print(std::vector<ClsValue> list)
    {
        if(0 < list.size())
        {
            size_t idx = 0, tail = list.size() - 1;
            for(auto & v : list)
            {
                std::cout << v.str();
                if(idx != tail) { std::cout << ", "; }
                idx ++;
            }
        }
    }

//---------------------------------------------------------------------------------------------------------------------
    void set_fmt(const std::string & str)
    {
        std::regex reg("^(.*):([^:]*)$");
        auto key = std::regex_replace(str, reg, "$1");
        auto fmt_str  = std::regex_replace(str, reg, "$2");
        std::regex freg(key);
        fmt_reg[key] = freg;
        fmt[key] = fmt_str;
    }
    void print(std::string & str)
    {
        bool crlf = false;
        if(f_grep)    { if(!std::regex_search(str, reg_grep)) { return; }       }
        if(f_pgrep)   { std::cout << str << std::endl;                          }
        if(f_replace) { str = std::regex_replace(str, reg_replace, rep_str);    }
        if(f_presp)   { std::cout << str << std::endl;;                         }
        BinaryControl bin(str);
        if(f_dump)    { std::cout << bin.dump() << ", "; }
        for(const auto & [ key, reg ] : fmt_reg)
        {
            auto str = bin.dump();
            if(std::regex_search(str, reg))
            {
                print(bin.get(fmt[key]));
                crlf = true;
                break;
            }
        }
        if(crlf) { std::cout << std::endl; }
    }
//---------------------------------------------------------------------------------------------------------------------
    void loadBinary(const std::string & str)
    {
        //std::string fname("file:");
        //fname += str;
        BinaryControl temp(str, 1);
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
            /* 0: */ [&]() { addr = reg_cmd.replace(str, idx, "$1"); list_addr.push_back(stoi(addr)); fmt = reg_cmd.replace(str, idx, "$2"); },
            /* 1: */ [&]() { addr = reg_cmd.replace(str, idx, "$1"); list_addr.push_back(stoi(addr)); fmt = reg_cmd.replace(str, idx, "$2"); auto n(reg_cmd.replace(str, idx, "$3")); count = stoi(n); },

            /* 2: */ [&]() { addr = reg_cmd.replace(str, idx, "$1"); list_addr = bin.toAddressList(addr); fmt = reg_cmd.replace(str, idx, "$2"); },
            /* 3: */ [&]() { addr = reg_cmd.replace(str, idx, "$1"); list_addr = bin.toAddressList(addr); fmt = reg_cmd.replace(str, idx, "$2"); auto n(reg_cmd.replace(str, idx, "$3")); count = stoi(n); },

            /* 4: */ [&]() { list_addr.push_back(0);                                                      find = reg_cmd.replace(str, idx, "$1"); fmt = reg_cmd.replace(str, idx, "$2"); },
            /* 5: */ [&]() { addr = reg_cmd.replace(str, idx, "$1"); list_addr.push_back(stoi(addr));     find = reg_cmd.replace(str, idx, "$2"); fmt = reg_cmd.replace(str, idx, "$3"); },
            /* 6: */ [&]() { addr = reg_cmd.replace(str, idx, "$1"); list_addr = bin.toAddressList(addr); find = reg_cmd.replace(str, idx, "$2"); fmt = reg_cmd.replace(str, idx, "$3"); }
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
    void print_csv(std::string & str, std::string & format)
    {
        bool crlf = false;
        if(f_grep)    { if(!std::regex_search(str, reg_grep)) { return; }       }
        if(f_pgrep)   { std::cout << str << std::endl;                          }
        if(f_replace) { str = std::regex_replace(str, reg_replace, rep_str);    }
        if(f_presp)   { std::cout << str << std::endl;;                         }
        CppRegexp reg({","});
        auto list = reg.split(str);
        BinaryControl bin;
        bin.set(list, format);
        std::cout << bin.dump() << std::endl;
    }
};

int main(int argc, char * argv[])
{
    try
    {
        boost::program_options::options_description desc("bin2format.exe [Options] arg");
        desc.add_options()
            ("file,f",       boost::program_options::value<std::string>(),                          "input file name"                                       )
            ("mode,m",       boost::program_options::value<std::string>()->default_value("conv"),   "select mode: [conv, bin, csv]"                         )
            ("grep,g",       boost::program_options::value<std::string>(),                          "Pre-execute Grep    ex) --grep 'Regexp'"               )
            ("replace,r",    boost::program_options::value<std::string>(),                          "Pre-execute Replace ex) --replace 'Regexp/Replace'"    )
            ("csv-format,c", boost::program_options::value<std::string>(),                          "csv format"                                            )
            ("print-address,a",                                                                     "print address"                                         )
            ("dump,d",                                                                              "print binary dump"                                     )
            ("print-grep",                                                                          "print grep result"                                     )
            ("print-replace",                                                                       "print replace result"                                  )
            ("version,v",                                                                           "Print version"                                         )
            ("help,h",                                                                              "help"                                                  );
        boost::program_options::variables_map argmap;
        auto const parsing_result = parse_command_line(argc, argv, desc);
        store(parsing_result, argmap);
        notify(argmap);

        if(argmap.count("version")) { printRevision(); return (0); }
        if(argmap.count("help"))    { printHelp(desc); return (0); }

        BinaryConverter bin;
        if(argmap.count("print-address"))   { bin.set_print_address(true); }
        if(argmap.count("dump"))            { bin.set_dump(true);          }
        if(argmap.count("print-grep"))      { bin.set_print_grep(true);    }
        if(argmap.count("print-replace"))   { bin.set_print_replace(true); }

        if(argmap.count("mode"))
        {
            CppRegexp reg_mode({ "^conv$", "^bin$", "^csv$"});
            auto mode = reg_mode.select(argmap["mode"].as<std::string>());
            auto mode_conv = [&]()
            {   /* format convert mode */
               for(auto const & str : collect_unrecognized(parsing_result.options, boost::program_options::include_positional)) { bin.set_fmt(str); }
               if((0 == bin.size()) && !(bin.is_print())) { printHelp(desc); return (0); }

               std::string str;
               if(argmap.count("grep"))            { str = argmap["grep"].as<std::string>();    bin.set_grep(str);    }
               if(argmap.count("replace"))         { str = argmap["replace"].as<std::string>(); bin.set_replace(str); }
               str.clear();
               if(argmap.count("file"))
               {
                   auto fname = argmap["file"].as<std::string>();
                   if(std::filesystem::exists(fname))
                   {
                       std::ifstream ifs(fname);
                       while(std::getline(ifs,str)) { bin.print(str); }
                   } else { std::cout << "file not found: " << fname << std::endl; return -1; }
               } else { while(std::getline(std::cin, str)) { bin.print(str); } }
               return 0;
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
                    } else { std::cout << "file not found: " << fname << std::endl; return -1; }
                }
                return 0;
            };
            auto mode_csv = [&]()
            {   /* csv mode */
                std::string str;
                if(argmap.count("grep"))     { str = argmap["grep"].as<std::string>();    bin.set_grep(str);    }
                if(argmap.count("replace"))  { str = argmap["replace"].as<std::string>(); bin.set_replace(str); }
                str.clear();
                if(argmap.count("csv-format"))
                {
                    auto fmt = argmap["csv-format"].as<std::string>();
                    if(argmap.count("file"))
                    {
                        auto fname = argmap["file"].as<std::string>();
                        if(std::filesystem::exists(fname))
                        {
                            std::ifstream ifs(fname);
                            while(std::getline(ifs,str)) { bin.print_csv(str, fmt); }
                        } else { std::cout << "file not found: " << fname << std::endl; return -1; }
                    } else { while(std::getline(std::cin, str)) { bin.print_csv(str, fmt); } }
                } else { std::cout << "not format option" << std::endl; return -2; }
                return 0;
            };
            std::vector<std::function<void()>> act = { mode_conv, mode_bin, mode_csv };
            if(mode < act.size()) { (act[mode])(); }
        } else { printHelp(desc); }
    }
    catch(const std::exception & e) { std::cout << "exeption: "       << e.what() << std::endl; return -2; }
    catch(...)                      { std::cout << "unknown exeption"             << std::endl; return -3; }
    return 0;
}
