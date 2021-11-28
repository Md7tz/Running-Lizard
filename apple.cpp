#include <graphics.h>
#include <string>
int main()
{
    initwindow(810,600);
  // your "Unicode" string
wchar_t const * utf16_string = L"U+1F34E";

// #include <codecvt>
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>,wchar_t> convert;

std::string utf8_string = convert.to_bytes(utf16_string);
    // char *txt = AnsiString(text).c_str();
    

}