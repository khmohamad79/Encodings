#pragma once
class Base64
{
    static const char mapping[];

public:
    bool bit5 : 1;
    bool bit4 : 1;
    bool bit3 : 1;
    bool bit2 : 1;
    bool bit1 : 1;
    bool bit0 : 1;

    /// <summary>
    /// represents 6-bit number in alphanumeric format
    /// </summary>
    /// <returns>ascii equivalent of encoded 6-bit</returns>
    operator char() const;

    /// <summary>
    /// encodes input string to base64 format
    /// </summary>
    /// <param name="inp_str">input string</param>
    /// <param name="inp_len">input string length</param>
    /// <returns>encoded string</returns>
    static char* encode(const char* inp_str, const int& inp_len);

    /// <summary>
    /// decodes input string from base64 format
    /// </summary>
    /// <param name="inp_str">input string</param>
    /// <param name="inp_len">input string length</param>
    /// <returns>decoded string</returns>
    static char* decode(const char* inp_str, const int& inp_len);
};

