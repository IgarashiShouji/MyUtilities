/* font attribute */
const char fontReset[]          = "\033[0m";
const char fontBold[]           = "\033[1m";
const char fontThin[]           = "\033[2m";
const char fontItalic[]         = "\033[3m";
const char fontUnderLine[]      = "\033[4m";
const char fontBlink[]          = "\033[5m";
const char fontHiBlink[]        = "\033[6m";
const char fontColorReverse[]   = "\033[7m";
const char fontHide[]           = "\033[8m";
const char fontStrikethrough[]  = "\033[9m";
/* font color */
const char fontBlack[]          = "\033[30m";
const char fontRed[]            = "\033[31m";
const char fontGreen[]          = "\033[32m";
const char fontYellow[]         = "\033[33m";
const char fontBlue[]           = "\033[34m";
const char fontMagellan[]       = "\033[35m";
const char fontCyan[]           = "\033[36m";
const char fontWhite[]          = "\033[37m";
const char fontBlackBack[]      = "\033[40m";
const char fontRedBack[]        = "\033[41m";
const char fontGreenback[]      = "\033[42m";
const char fontYellowBack[]     = "\033[43m";
const char fontBlueBack[]       = "\033[44m";
const char fontMagellanBack[]   = "\033[45m";
const char fontCyanBack[]       = "\033[46m";
const char fontWhiteBack[]      = "\033[47m";
const char fontColorCode[]      = "\033[38;5;%dm";
const char fontColorCodeBack[]  = "\033[48;5;%dm";
const char fontRGB[]            = "\033[38;2;%d;%d;%dm";
const char fontRGBBack[]        = "\033[48;2;%d;%d;%dm";
/* screen clear */
const char scrClearCurBack[]    = "\033[0J";
const char scrClearCurFront[]   = "\033[1J";
const char scrClear[]           = "\033[2J";
const char lineClearCurBack[]   = "\033[0K";
const char lineRemoveCurFront[] = "\033[1K";
const char lineRemove[]         = "\033[2K";
/* cursor move */
const char curUP[]              = "\033[1A";
const char curDown[]            = "\033[1B";
const char curRtiht[]           = "\033[1C";
const char curLeft[]            = "\033[1D";
const char curUpLineTop[]       = "\033[1F";
const char curDownLineTop[]     = "\033[1E";
const char curMoveLeft[]        = "\033[%dG";
const char curMoveTopLeft[]     = "\033[%d;%dH";
#if 0
const char * curMoveTopLeft     = "\033[%d;%df";
#endif
/* Scroll */
const char curUpScroll[]        = "\033e[1S";
const char curUpScrolln[]       = "\033e[%dS";
const char curDownScroll[]      = "\033[1T";
const char curDownScrolln[]     = "\033[%dT";
